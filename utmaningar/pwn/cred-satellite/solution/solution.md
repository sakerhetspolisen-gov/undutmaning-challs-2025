# Solution
1. Find UAF vulnerability in kernel module. 
   - Allocate a victim block with `IOCTL_ALLOC`
   - Set the victim block as current block with `IOCTL_SET_CURRENT`.
   - Free the victim block with `IOCTL_SET_CURRENT`.
   - Trigger UAF on victim block with `IOCTL_RESET_CURRENT`
2. Setup local develop environment where user is root (for development and debugging).
   1. Run `decompress.sh`.
   2. Change `setuidgid 1000 sh`to `setuidgid 0 sh `in
      `./initram/etc/inittab`.
   3. Run `compress.sh`.
   4. Run VM with `run.sh`. Vulnerable driver debug output found by running
      `dmesg` in VM.
3. Build exploit: 
   1. Initiate a bunch of sprayer threads.
   2. Do a cross-cache attack, technique presented in the blog post 'How a
      simple Linux kernel memory corruption bug can lead to complete system
      compromise' by GoogleProjectZero (hinted in challenge description).  Move
      the victim block from `kmalloc_256` to `cred_jar`. Slab information found
      in `/proc/slabinfo` and `/sys/kernel/slab/kmalloc-256` on VM. 
      1. De-fragment `kmalloc_256` slabs by allocating a large number of blocks
      2. Allocate (`obj_per_slab` * (1+`CPU_PARTIAL`)) blocks. 
      3. Allocate (`OBJ_PER_SLAB` - 1) blocks.
      4. Allocate victim block with `IOCTL_ALLOC` and set as current with
         `IOCTL_SET_CURRENT`.
      5. Allocate (`OBJ_PER_SLAB` + 1) blocks.
      6. Free blocks from step 3, 4 and 5. 
      7. Free one block per `OBJ_PER_SLAB` from step 2.
      8. Vulnerable object should now be at the page allocator.
   3. Trigger spray threads and spray `struct cred` objects using
      `syscall(__NR_setuid, current_uid)`.
   4. Trigger UAF with `IOCTL_RESET_CURRENT` to overwrite one of the threads
      cred structure with 0. UAF will overwrite:
      
```
include/linux/cred.h
  struct cred {
        ...
	    kuid_t		uid;		/* real UID of the task */
	    kgid_t		gid;		/* real GID of the task */
	    kuid_t		suid;		/* saved UID of the task */
	    kgid_t		sgid;		/* saved GID of the task */
	    kuid_t		euid;		/* effective UID of the task */
	    kgid_t		egid;		/* effective GID of the task */
        ...
  }
```
    (Source code for kernel found at `https://cdn.kernel.org/pub/linux/kernel/v5.x/`.)
  5. Check UID from spray threads, if `uid=0`, spawn shell.
