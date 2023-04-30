

#ifndef HARDWARE
#define HARDWARE


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

#endif