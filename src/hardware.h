

#ifndef HARDWARE
#define HARDWARE


/* clock control */
#define CLOCK_BASE           _BASE(0x40000000)
#define CLOCK_HFCLKSTART     _REG(unsigned, 0x40000000)
#define CLOCK_LFCLKSTART     _REG(unsigned, 0x40000008)
#define CLOCK_HFCLKSTARTED   _REG(unsigned, 0x40000100)
#define CLOCK_LFCLKSTARTED   _REG(unsigned, 0x40000104)
#define CLOCK_LFCLKSRC       _REG(unsigned, 0x40000518)
#define CLOCK_LFCLKRC_RC     0
#define CLOCK_XTALFREQ_16MHz 0xFF

/* NVMC */
#define NVMC_BASE _BASE(0x4001E000)
#define NVMC_READY _REG(unsigned, 0x4001E400)
#define NVMC_CONFIG _REG(unsigned, 0x4001E504)
#define NVMC_ERASEPAGE _REG(unsigned, 0x4001E508)
#define NVMC_ICACHECONF _REG(unsigned, 0x4001E540)
#define NVMC_CONFIG_WEN __BIT(0)
#define NVMC_CONFIG_EEN __BIT(1)
#define NVMC_ICACHECONF_CACHEEN __BIT(0)

/* GIPO */
#define GIPO0_BASE _BASE(0x50000500)
#define GPIO0_OUT _REG(unsigned, 0x50000504)
#define GPIO0_DIR _REG(unsigned, 0x50000514)

#define GIPO1_BASE _BASE(0x50000800)
#define GPIO1_OUT _REG(unsigned, 0x50000804)
#define GPIO1_DIR _REG(unsigned, 0x50000814)


/* led matrix */
#define _ROW(r, c1, c2, c3, c4, c5) \
    BIT(r) | (!c1 << 28) | (!c2 << 11) | (!c3 << 31) | (!c5 << 30) | (!c4 << 5)

#define LED_MASK0 0xD1688800
#define LED_MASK1 0x00000020

/* DMA layout*/
typedef struct {
    void* PTR;
    unsigned MAXCNT;
    unsigned AMOUNT;
} dma_param;

/* UARTE */

/* assembly macros */
#define pause() asm volatile ("wfe")
#define nop() asm volatile ("nop")

#endif