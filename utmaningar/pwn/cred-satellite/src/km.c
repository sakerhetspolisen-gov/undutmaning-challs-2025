#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/moduleloader.h>
#include <linux/device.h>
#include <linux/mm.h>

// Why do we still have this here??
#include <linux/slab.h>
#define __NR_setuid 105

MODULE_AUTHOR("Laika");
MODULE_DESCRIPTION("CRED-satellite block module");
MODULE_LICENSE("GPL"); // Custom init and exit methods

// Found as /dev/cred-block-module
#define DEV_NAME "cred-block-module"

#define IOCTL_FREE 0x1337
#define IOCTL_ALLOC 0x1338
#define IOCTL_SET_CURRENT 0x1339
#define IOCTL_RESET_CURRENT 0x1340
#define IOCTL_RESET_MODULE 0x1341

#define MAX_BLOCKS 1000

static int major_no;
static struct class *class;

struct data_block {
    u64 id;
    u64 valid;
    u8 data[200];
};

struct data_block *current_block;
int block_nr = 0;
struct data_block *myblocks[MAX_BLOCKS];

int free_block(int i) {    
    if (i < 0 || i >= MAX_BLOCKS || !myblocks[i])
        return -1;    
    printk(KERN_INFO "%s: freeing block myblocks[%d]=%px page=%px\n",
           __func__, i, myblocks[i], virt_to_head_page(myblocks[i]));
    kfree(myblocks[i]);
    myblocks[i] = NULL;
    return 0;
}

int alloc_block(void) {
    struct data_block *block;
    if (block_nr >= MAX_BLOCKS) {
        printk(KERN_INFO "Max number of blocks allocated");
        return -1;
    }
        
    block = kmalloc(sizeof(struct data_block), GFP_KERNEL);
    if (!block) {
        return -1;
    }    
    myblocks[block_nr] = block;
    printk(KERN_INFO "allocated myblocks[%d]=%px page=%px\n",
           block_nr, myblocks[block_nr], virt_to_head_page(myblocks[block_nr]));
    block->id = block_nr;
    return block_nr++;
}

int set_current_block(int i) {
    if (i < 0 || i >= MAX_BLOCKS || !myblocks[i])
        return -1;
    
    current_block = myblocks[i];
    printk(KERN_INFO "current block=%px page=%px\n",
           current_block, virt_to_head_page(current_block));

    return 0;
}

int reset_current_block(int i) {
    if (!current_block)
        return -1;
    printk(KERN_INFO "%s: resetting block %px page=%px\n",
           __func__, current_block, virt_to_head_page(current_block));
    memset(&current_block->valid, 0, 24); 
    return 0;
}

int reset_module(void) {
    int i;
    current_block = NULL;
    for (i = 0; i < block_nr; ++i) {
        if (myblocks[i]) {
            kfree(myblocks[i]);
            myblocks[i] = NULL;
        }        
    }
    block_nr = 0;
    printk(KERN_INFO "%s: all blocks removed!\n", __func__);
    return 0;
}

static long custom_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    static long ret = 0;
    switch(cmd) {
    case IOCTL_FREE:
        ret = free_block(arg);
        break;
    case IOCTL_ALLOC:
        ret = alloc_block();
        break;
    case IOCTL_SET_CURRENT:
        ret = set_current_block(arg);
        break;
    case IOCTL_RESET_CURRENT:
        ret = reset_current_block(arg);
        break;
    case IOCTL_RESET_MODULE:
        ret = reset_module();
        break;
    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}


static int custom_open(struct inode *in, struct file *f) { return 0; }


static int custom_release(struct inode *in, struct file *f) { return 0; }


static struct file_operations fops = {
    .unlocked_ioctl = custom_ioctl,
    .open = custom_open,
    .release = custom_release,
};



static int __init custom_init(void) {
  major_no = register_chrdev(0, DEV_NAME, &fops);
  class = class_create(THIS_MODULE, DEV_NAME);
  device_create(class, NULL, MKDEV(major_no, 0), NULL, DEV_NAME);
  
  printk(KERN_INFO DEV_NAME " device loaded.");
  return 0;
}


static void __exit custom_exit(void) {
    device_destroy(class, MKDEV(major_no, 0));
    class_unregister(class);
    class_destroy(class);
    unregister_chrdev(major_no, DEV_NAME);
        
  printk(KERN_INFO "Over and out!");
}

module_init(custom_init);
module_exit(custom_exit);
