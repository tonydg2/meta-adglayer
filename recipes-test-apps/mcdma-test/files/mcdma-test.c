// mcdma-test.c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h>

#define MCDMA_BASE_ADDR 0xA0000000
#define MCDMA_SIZE 0x10000

MODULE_LICENSE("GPL"); // required or compilation fails
//MODULE_AUTHOR("Your Name");
//MODULE_DESCRIPTION("MCDMA Test Kernel Module");
//MODULE_VERSION("0.01");

static void __iomem *mcdma_base;

static int __init mcdma_test_init(void) {
    printk(KERN_INFO "MCDMA Test Module Loaded\n");

    mcdma_base = ioremap(MCDMA_BASE_ADDR, MCDMA_SIZE);
    if (!mcdma_base) {
        printk(KERN_ERR "Failed to map MCDMA base address\n");
        return -ENOMEM;
    }

    // Example read and write
    u32 reg_val; 
    reg_val = ioread32(mcdma_base + 0x0);//default 0
    printk(KERN_INFO "MCDMA 0 register value: 0x%08x\n", reg_val);
    reg_val = ioread32(mcdma_base + 0x4);//default 1
    printk(KERN_INFO "MCDMA 4 register value: 0x%08x\n", reg_val);
    reg_val = ioread32(mcdma_base + 0x18);//default 0x111111111
    printk(KERN_INFO "MCDMA 18 register value: 0x%08x\n", reg_val);


    reg_val = ioread32(mcdma_base + 0x8); //default 1
    printk(KERN_INFO "MCDMA 8 register value: 0x%08x\n", reg_val);
    iowrite32(0x1, mcdma_base + 0x8);
    reg_val = ioread32(mcdma_base + 0x8);
    printk(KERN_INFO "New MCDMA 8 register value: 0x%08x\n", reg_val);
    iowrite32(0x2, mcdma_base + 0x8);
    reg_val = ioread32(mcdma_base + 0x8);
    printk(KERN_INFO "New MCDMA 8 register value: 0x%08x\n", reg_val);

    return 0;
}

static void __exit mcdma_test_exit(void) {
    iounmap(mcdma_base);
    printk(KERN_INFO "MCDMA Test Module Unloaded\n");
}

module_init(mcdma_test_init);
module_exit(mcdma_test_exit);
