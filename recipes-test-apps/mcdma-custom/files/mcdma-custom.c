// mcdma-custom.c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h>
//#include <linux/unistd.h> // NOT available for kernel space! This is for user-space programs
#include <linux/delay.h> // specfically for kernel space - udelay(), usleep_range()

//#define MCDMA_BASE_ADDR 0xA0000000
#define MCDMA_SIZE      0x10000
//#define MEM_BASE_ADDR   0xC0000000
#define MEM_SIZE        0x10000 //8192
//#define SG_BASE_ADDR    0xA0010000
#define SG_SIZE         0x10000 //2048

#define REG32_ADDR 0xA0012000
#define REG32_SIZE 0x1000

#define ADDR_SG  0xA0010000
#define ADDR_DMA 0xA0000000
#define ADDR_MEM 0xC0000000
#define ADDR_REG 0xA0012000
#define NXDS_S0  0x00
#define BADD_S0  0x08
#define CTRL_S0  0x14
#define NXDS_S1  0x40
#define BADD_S1  0x48
#define CTRL_S1  0x54
#define NXDS_M0  0x80
#define BADD_M0  0x88
#define CTRL_M0  0x94
#define NXDS_M1  0xC0
#define BADD_M1  0xC8
#define CTRL_M1  0xD4
#define MM2S_CR  0x000
#define MM2S_SR  0x004
#define MM2S_CH  0x008
#define MM2S_PR  0x00C
#define MM2S_ER  0x010
#define MM2S_CQ  0x014
#define MM2S_CC  0x020
#define M_CH0CR  0x040
#define M_CH0CD  0x048
#define M_CH0TD  0x050
#define M_CH1CR  0x080
#define M_CH1CD  0x088
#define M_CH1TD  0x090
#define S2MM_CR  0x500
#define S2MM_SR  0x504
#define S2MM_CH  0x508
#define S2MM_PR  0x50C
#define S2MM_ER  0x510
#define S2MM_CQ  0x514
#define S2MM_CC  0x520
#define S_CH0CR  0x540
#define S_CH0CD  0x548
#define S_CH0TD  0x550
#define S_CH1CR  0x580
#define S_CH1CD  0x588
#define S_CH1TD  0x590

MODULE_LICENSE("GPL"); // required or compilation fails
//MODULE_AUTHOR("Your Name");
//MODULE_DESCRIPTION("MCDMA Test Kernel Module");
//MODULE_VERSION("0.01");

static void __iomem *mcdma_base;
static void __iomem *sg_base; // sg bram
static void __iomem *mem_base; // mem bram
static void __iomem *reg32_base; // reg32 timestamp/githash

//int usleep(useconds_t usec);
//unsigned int sleep(unsigned int seconds);

static void mcdmaCfg(void);
static void mcdmaReset(void);
static void mcdmaStatus(void);
static void readSG(void);
static void clearSG(void);
//static u32  Xil_In32(u32 addr);
//static void Xil_Out32(u32 addr,u32 data);

static int __init mcdma_custom_init(void) {
  u32 val;
  
  printk(KERN_INFO "MCDMA Test Module Loaded\n");
  mcdma_base = ioremap(ADDR_DMA, MCDMA_SIZE);
  if (!mcdma_base) {
      printk(KERN_ERR "Failed to map MCDMA base address\n");
      return -ENOMEM;
  }
  sg_base = ioremap(ADDR_SG, SG_SIZE);
  if (!sg_base) {
      printk(KERN_ERR "Failed to map sg_base address\n");
      return -ENOMEM;
  }
  mem_base = ioremap(ADDR_MEM, MEM_SIZE);
  if (!mem_base) {
      printk(KERN_ERR "Failed to map MCDMA base address\n");
      return -ENOMEM;
  }
  reg32_base = ioremap(REG32_ADDR, REG32_SIZE);
  if (!reg32_base) {
      printk(KERN_ERR "Failed to map REG32 base address\n");
      return -ENOMEM;
  }

  val = ioread32(reg32_base);
  printk(KERN_INFO "REG32 register value: 0x%08x\n", val);
  val = ioread32(reg32_base + 0x18);
  printk(KERN_INFO "REG32 0x18 register value: 0x%08x\n", val);
  iowrite32(0xAA550127, reg32_base + 0x18);
  val = ioread32(reg32_base + 0x18);
  printk(KERN_INFO "REG32 0x18 register value: 0x%08x\n", val);

  printk(KERN_INFO "\n----------------------------------------\n");
  printk(KERN_INFO "MCDMA Test2\n");
  printk(KERN_INFO "----------------------------------------\n");
  
  //udelay(4);printk(KERN_INFO "udelay\n");
  //msleep(4000);printk(KERN_INFO "sleep4\n");
  //msleep(4000);printk(KERN_INFO "sleep4\n");
  
  readSG();mcdmaStatus();
  
  mcdmaCfg();readSG();mcdmaStatus();
  mcdmaReset();
  clearSG();readSG();mcdmaStatus();
  msleep(4000);
  
  for(int x=0;x<5;x++){
    mcdmaCfg();
    mcdmaReset();
    clearSG();
    msleep(4000);
  }

  iounmap(mcdma_base);
  iounmap(sg_base);
  iounmap(mem_base);
  iounmap(reg32_base);
  
  return 0;
}

void readSG(void) {
    
    u32 val,reg;
    
    for(u32 x=0;x<=0x10C;x=x+0x4) {
      reg = x; val = ioread32(sg_base + reg);  printk(KERN_INFO "%x = %x\n\r",reg,val);
    }

    printk(KERN_INFO "\n\r*************** SG READ ****************\n\r");
}

void clearSG(void) {

    u32 reg;

    for(u32 x=0;x<=0x10C;x=x+0x4) {
      reg = x; iowrite32(0x0, sg_base + reg);
    }

    printk(KERN_INFO "\n\r*************** SG CLEAR ****************\n\r");
}

void mcdmaStatus(void) {

    u32 val;
    val = ioread32(mcdma_base + MM2S_CR);   printk(KERN_INFO "MM2S_CR = %x\n\r",val);
    val = ioread32(mcdma_base + MM2S_SR);   printk(KERN_INFO "MM2S_SR = %x\n\r",val);
    val = ioread32(mcdma_base + MM2S_CH);   printk(KERN_INFO "MM2S_CH = %x\n\r",val);
    val = ioread32(mcdma_base + MM2S_PR);   printk(KERN_INFO "MM2S_PR = %x\n\r",val);
    val = ioread32(mcdma_base + MM2S_ER);   printk(KERN_INFO "MM2S_ER = %x\n\r",val);
    val = ioread32(mcdma_base + MM2S_CQ);   printk(KERN_INFO "MM2S_CQ = %x\n\r",val);
    val = ioread32(mcdma_base + MM2S_CC);   printk(KERN_INFO "MM2S_CC = %x\n\r",val);

    val = ioread32(mcdma_base + S2MM_CR);   printk(KERN_INFO "S2MM_CR = %x\n\r",val);
    val = ioread32(mcdma_base + S2MM_SR);   printk(KERN_INFO "S2MM_SR = %x\n\r",val);
    val = ioread32(mcdma_base + S2MM_CH);   printk(KERN_INFO "S2MM_CH = %x\n\r",val);
    val = ioread32(mcdma_base + S2MM_PR);   printk(KERN_INFO "S2MM_PR = %x\n\r",val);
    val = ioread32(mcdma_base + S2MM_ER);   printk(KERN_INFO "S2MM_ER = %x\n\r",val);
    val = ioread32(mcdma_base + S2MM_CQ);   printk(KERN_INFO "S2MM_CQ = %x\n\r",val);
    val = ioread32(mcdma_base + S2MM_CC);   printk(KERN_INFO "S2MM_CC = %x\n\r",val);

    printk(KERN_INFO "\n\r*************** MCDMA STATUS ****************\n\r");

}

void mcdmaReset(void) {

    iowrite32(0x4, mcdma_base + MM2S_CR);        // reset DMA both MM2S and SS2M
    udelay(4);
    printk(KERN_INFO "\n\r*************** MCDMA RESET ****************\n\r");

}

void mcdmaCfg(void) {
    // LINUX Kernel module
    // For the descriptors that are populated into the SG BRAM, 
    //  these need to be the direct HW AXI addresses, not the virtual addresses returned by ioremap
    //  the MCDMA accesses the AXI interface using these direct HW addresses
    //  ADDR_DMA, ADDR_SG, ADDR_MEM
    // data = HW address, addr = virtual kernel address
    // iowrite32(data,addr)


    //S2MM descriptors
    /* CH0 1st descriptor, store 8bytes - two 32bit words */
    iowrite32(ADDR_SG + NXDS_S0 , sg_base + NXDS_S0); // point to next descriptor
    iowrite32(ADDR_MEM + 0x0    , sg_base + BADD_S0); // location to store data
    iowrite32(ADDR_MEM + 0x40   , sg_base + CTRL_S0);// 0xC0000040 //(0x0, 0x1, 0x1, 0x0, 0x40)); // RXSOF, REOF, Reserved, Len
    /* CH1 1st descriptor, store 8bytes - two 32bit words */
    iowrite32(ADDR_SG + NXDS_S1 , sg_base + NXDS_S1); // point to next descriptor
    iowrite32(ADDR_MEM + 0x1000 , sg_base + BADD_S1); // location to store data
    iowrite32(ADDR_MEM + 0x40   , sg_base + CTRL_S1); // RXSOF, REOF, Reserved, Len

    //MM2S descriptors different location
    //CH0
    iowrite32(ADDR_SG + NXDS_M0 , sg_base + NXDS_M0); // point to next descriptor
    iowrite32(ADDR_MEM + 0x1000 , sg_base + BADD_M0); // location to get data
    iowrite32(ADDR_MEM + 0x40   , sg_base + CTRL_M0); // RXSOF, REOF, Reserved, Len
    //CH1
    iowrite32(ADDR_SG + NXDS_M1 , sg_base + NXDS_M1); // point to next descriptor
    iowrite32(ADDR_MEM + 0x0    , sg_base + BADD_M1); // location to get data
    iowrite32(ADDR_MEM + 0x40   , sg_base + CTRL_M1); // RXSOF, REOF, Reserved, Len

    //---------------------------------------------------------------------------------------------
    //S2MM DMA config
    //---------------------------------------------------------------------------------------------
    // config. DMA for descriptor location and initiate/start transfers
    iowrite32(              0x3, mcdma_base + S2MM_CH);              // enable channels
    iowrite32(ADDR_SG + NXDS_S0, mcdma_base + S_CH0CD);  // CD for ch0
    iowrite32(ADDR_SG + NXDS_S1, mcdma_base + S_CH1CD);  // CD for ch1
    iowrite32(              0x1, mcdma_base + S_CH0CR);        // ch0 fetch bit
    iowrite32(              0x1, mcdma_base + S_CH1CR);        // ch1 fetch bit
    iowrite32(              0x1, mcdma_base + S2MM_CR);        // start DMA
    iowrite32(ADDR_SG + NXDS_S0, mcdma_base + S_CH0TD);  // TD for ch0
    iowrite32(ADDR_SG + NXDS_S1, mcdma_base + S_CH1TD);  // TD for ch1

    //#200;
    //done<=1;
    //#4us;
    udelay(4);
    //---------------------------------------------------------------------------------------------
    //MM2S DMA config
    //---------------------------------------------------------------------------------------------
    iowrite32(              0x3, mcdma_base + MM2S_CH);        // enable channels
    iowrite32(ADDR_SG + NXDS_M0, mcdma_base + M_CH0CD);  // CD for ch0
    iowrite32(ADDR_SG + NXDS_M1, mcdma_base + M_CH1CD);  // CD for ch1
    iowrite32(              0x1, mcdma_base + M_CH0CR);        // ch0 fetch bit
    iowrite32(              0x1, mcdma_base + M_CH1CR);        // ch1 fetch bit
    iowrite32(              0x1, mcdma_base + MM2S_CR);        // start DMA
    iowrite32(ADDR_SG + NXDS_M0, mcdma_base + M_CH0TD);  // TD for ch0
    iowrite32(ADDR_SG + NXDS_M1, mcdma_base + M_CH1TD);  // TD for ch1

    printk(KERN_INFO "\n\r*************** MCDMA DONE ****************\n\r");

}

//void mcdmaCfg(void) {
//  u32 val;
//  
//  printk(KERN_INFO "mcdmaCfg *******\n");
//  val = ioread32(reg32_base);
//  printk(KERN_INFO "REG32 register value: 0x%08x\n", val);
//  val = ioread32(reg32_base + 0x18);
//  printk(KERN_INFO "REG32 0x18 register value: 0x%08x\n", val);
//  iowrite32(0xAA550127, reg32_base + 0x18);
//  val = ioread32(reg32_base + 0x18);
//  printk(KERN_INFO "REG32 0x18 register value: 0x%08x\n", val);
//
//}


static void __exit mcdma_custom_exit(void) {
    iounmap(mcdma_base);
    printk(KERN_INFO "MCDMA Test Module Unloaded\n");
}

module_init(mcdma_custom_init);
module_exit(mcdma_custom_exit);



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