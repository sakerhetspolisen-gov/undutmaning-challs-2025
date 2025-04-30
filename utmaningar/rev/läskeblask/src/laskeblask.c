#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>

#include <sys/mman.h>
#include <sys/syscall.h>

#include "realpassword.h"

int main(int ac, char **av);
int init(void) __attribute__((constructor));
int checkpassword(char *password);
static inline void *memsearch(void *src, size_t slen, void *dst, size_t dlen) __attribute__((always_inline));

char PASSWORD[] = "s3kr37p455w0rDMuStb3Unkn0wn";
//const char PASSWORD[] = "asdf";
unsigned long g_fptr;
//#define DEBUG

#define ALLOW_STACK_OVERWRITE
#define XORBYTE 0x80

extern char __etext, _edata, data_start, __executable_start;

int main(int ac, char **av)
{
    char pbuf[128];

    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Accessing flag");
#ifndef DEBUG
    // Slow program down a bit..
    for (int i=0; i < 8; i++) {
        usleep(100000);
        printf(".");
    }
#endif

    printf("\nMust have password:\n");
    fgets(pbuf, sizeof(pbuf), stdin);
    char *ptr = strchr(pbuf, '\n');
    if (ptr) *ptr = 0;
#ifdef DEBUG
    fprintf(stderr, "[DEBUG] Read -> \"%s\"\n", pbuf);
#endif
    

    if (checkpassword(pbuf)) {
        char flagbuf[64];
        int fd = open("flag.txt", O_RDONLY);
        if (-1 == fd) {
            perror("open");
            exit(1);
        }
        memset(flagbuf, 0, sizeof(flagbuf));
        int status = read(fd, flagbuf, sizeof(flagbuf) - 1);
        if (-1 == status) {
            perror("read");
            exit(1);
        }
        printf("Correct password entered\n");
        printf("Have a flag!\n%s\n", flagbuf);
        close(fd);
    } else {
        printf("Wrong pasword\n");
    }

    return 0;
}

int init(void)
{
    int needle;
    char *passptr;
    void *ptr;

#ifdef DEBUG
    fprintf(stderr, "[DEBUG] .text %p\n", &__etext);
    fprintf(stderr, "[DEBUG] .data %p\n", &data_start);
    fprintf(stderr, "[DEBUG] es %p\n", &__executable_start);
#endif

    // Find password string without directly referincing it
    needle = *(int *)"s3kr";
#ifdef DEBUG
    fprintf(stderr, "[DEBUG] needle : \"%s\"\n", &needle);
#endif
    ptr = memsearch(&data_start, 0x2000, &needle, sizeof(needle));
    
    char tmppass[] = REALPASSWORD;
    
#ifdef DEBUG
    for (int i=0; i < sizeof(tmppass); i++) {
        fprintf(stderr, "[DEBUG] tmppass[%i] == 0x%.02x\n", i, 0xff&tmppass[i]);
    }
#endif
    memcpy(ptr, tmppass, sizeof(tmppass));
    *(char *)(ptr+REALPASSLEN) = 0 ^ XORBYTE;
    for (int i=0; i < sizeof(tmppass); i++) {
        int tmp = *(char *)(ptr+i);
        // tmp = (ord(REALPASS[i]) + (2 << (i%3))) % 0x100 // The python code
        tmp = tmp - (2 << i%3) % 0x100;
        *(char *)(ptr+i) = tmp;
    }


    int status = syscall(SYS_mprotect,&__executable_start, 0x2000, PROT_EXEC|PROT_WRITE|PROT_READ);
    if (0 != status) {
        perror("mprotect");
    }

    needle = (0xdead << 16);
    needle |= 0xbeef0000>>16;
    ptr = memsearch(&__executable_start, 0x2000, &needle, sizeof(needle));
#ifdef DEBUG
    fprintf(stderr, "[DEBUG] found deadbeef %p\n", ptr);
    fprintf(stderr, "[DEBUG] Verification 0x%lx\n", *(uint32_t *)ptr);
#endif

    // Get address of "hidden strcmp"
    unsigned long fptr = 0;
    asm("jmp 2f");
    asm("3:");
    asm("pop %0" : "=r"(fptr) :: );
#ifdef DEBUG
    fprintf(stderr, "[DEBUG] FPointer mystrcmp %li\n", fptr);
#endif
    g_fptr = fptr;

    ushort *patch_jmp = ptr - 2;
#ifdef DEBUG
    fprintf(stderr, "[DEBUG] Bytes at patch location %.04x\n", *patch_jmp);
#endif
    *patch_jmp++ = 0x9090;
    *patch_jmp++ = 0x9090;
    *patch_jmp++ = 0x9090;


}

// strcmp
asm (".section .text\n"
    "2:\n"
    "call 3b\n"
    "5:\n"
    "movb (%rdi), %al\n"
    "xorb $0x80, %al\n"
    "subb (%rsi), %al\n"
    "jne 6f\n"
    "cmpb $0, (%rdi)\n"
    "je 6f\n"
    "cmpb $0, (%rsi)\n"
    "je 6f\n"
    "inc %rdi\n"
    "inc %rsi\n"
    "jmp 5b\n"
    "6:\n"
    "and $0xff, %rax\n"
    "ret\n"
);

int checkpassword(char *password)
{
    int retval;
    int status;

    // do "strcmp" call
    asm volatile (
        "jmp 1f\n"
        ".long 0xdeadbeef\n"
        "mov %3, %%rax\n" // call rax
        "call *%%rax\n"
        "jmp 1000f\n"
        "1:\n"
        "call strcmp\n"
        "1000: mov %%eax, %0"
        : "=r"(status)
        : "D"(password),
          "S"(PASSWORD),
          "r"(g_fptr)
        : "rax");
#ifdef DEBUG
    fprintf(stderr, "[DEBUG] strcmp() == %li\n", status);
#endif
    if (!status)
        retval = 1;
    else
        retval = 0;

#ifdef DEBUG
    fprintf(stderr, "[DEBUG] passcompare \"%s\", \"%s\" == %i\n", PASSWORD, password, retval);
    fprintf(stderr, "[DEBUG] Real password is : \"");
    for (int i=0; i < REALPASSLEN; i++) fprintf(stderr, "%c", PASSWORD[i] ^ XORBYTE);
    fprintf(stderr, "\"\n");
#endif

    return retval;
}

static inline void *memsearch(void *src, size_t slen, void *dst, size_t dlen)
{
    void *sptr;
    void *dptr, *dbptr;

    for (sptr = src; sptr < (src+slen-dlen); sptr++) {
        for (dbptr = sptr, dptr = dst; dptr < (dst+dlen); dptr++, dbptr++)
            if (*(char *)dbptr - *(char *)dptr) break; // Not equal
        // Check for finding needle
        if (dptr == dst+dlen) return sptr;
    }
    return NULL;
}
