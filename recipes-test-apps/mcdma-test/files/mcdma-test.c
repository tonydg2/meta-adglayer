// mcdma-test.c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h>

#define MCDMA_BASE_ADDR 0xA0000000
#define MCDMA_SIZE      0x10000
#define MEM_BASE_ADDR   0xC0000000
#define MEM_SIZE        8192
#define SG_BASE_ADDR    0xA0010000
#define SG_SIZE         2048

#define TX_BD_SPACE_BASE  (SG_BASE_ADDR)
#define RX_BD_SPACE_BASE  (SG_BASE_ADDR + 0x1000)

#define TX_BUFFER_BASE  (MEM_BASE_ADDR)
#define RX_BUFFER_BASE  (MEM_BASE_ADDR)


MODULE_LICENSE("GPL"); // required or compilation fails
//MODULE_AUTHOR("Your Name");
//MODULE_DESCRIPTION("MCDMA Test Kernel Module");
//MODULE_VERSION("0.01");

static void __iomem *mcdma_base;
static void __iomem *sg_base; // sg bram
static void __iomem *mem_base; // mem bram

static int __init mcdma_test_init(void) {
  printk(KERN_INFO "MCDMA Test Module Loaded\n");
  mcdma_base = ioremap(MCDMA_BASE_ADDR, MCDMA_SIZE);
  if (!mcdma_base) {
      printk(KERN_ERR "Failed to map MCDMA base address\n");
      return -ENOMEM;
  }
  sg_base = ioremap(SG_BASE_ADDR, SG_SIZE);
  if (!sg_base) {
      printk(KERN_ERR "Failed to map sg_base address\n");
      return -ENOMEM;
  }
  mem_base = ioremap(MEM_BASE_ADDR, MEM_SIZE);
  if (!mem_base) {
      printk(KERN_ERR "Failed to map MCDMA base address\n");
      return -ENOMEM;
  }



  iounmap(mcdma_base);
  iounmap(sg_base);
  iounmap(mem_base);
  return 0;
}

static void __exit mcdma_test_exit(void) {
    iounmap(mcdma_base);
    printk(KERN_INFO "MCDMA Test Module Unloaded\n");
}

module_init(mcdma_test_init);
module_exit(mcdma_test_exit);



/*
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
*/