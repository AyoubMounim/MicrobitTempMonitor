
#include "clock.h"
#include "nvmc.h"
#include "macros.h"


/* jump to main */
void main(void);

void default_start(void){
    hardware_init();
    main();
    while (1) pause();
}


/* memory management functions */
void* memcpy(void* dest, const void* src, unsigned n){
    unsigned char* p = dest;
    const unsigned char* q = src;
    while (n-- > 0){
        *p++ = *q++;
    }
    return dest;
}

void* memmove(void* dest, const void* src, unsigned n){
    unsigned char* p = dest;
    const unsigned char* q = src;
    if (dest <= src){
        while (n-- > 0){*p++ = *q++;}
    }
    else {
        p += n;
        q += n;
        while (n-- > 0){*--p = *--q;}
    }
    return dest;
}

void* memset(void* dest, unsigned x, unsigned n){
    unsigned char *p = dest;
    while (n-- > 0){
        *p++ = x;
    }
    return dest;
}

int memcmp(const void* pp, const void* qq, int n){
    const unsigned char* p = pp;
    const unsigned char* q = qq;
    while (n-- > 0){
        if (*p++ != *q++){
            return (p[-1] < q[-1] ? -1 : 1);
        }
    }
    return 0;
}


/* initialization functions */
void clock_init(void){
    CLOCK_HFCLKSTARTED = 0;
    CLOCK_HFCLKSTART = 1;
    while (!CLOCK_HFCLKSTARTED){}
    return;
}

void cache_init(void){
    SET_BIT(NVMC_ICACHECONF, NVMC_ICACHECONF_CACHEEN);
    return;
}

void hardware_init(void){
    clock_init();
    cache_init();
    return;
}


/* memory addresses from linker script */
extern unsigned char _text_end[];
extern unsigned char _xram_start[];
extern unsigned char _xram_end[];
extern unsigned char _data_start[];
extern unsigned char _data_end[];
extern unsigned char _bss_start[];
extern unsigned char _bss_end[];
extern unsigned char _end[];
extern unsigned char _stack[];

/* entry point */
void _reset(void){
    int xram_size = _xram_end - _xram_start;
    int data_size = _data_end - _data_start;
    int bss_size = _bss_end - _bss_start;
    memcpy(_xram_start, _text_end, xram_size);
    memcpy(_data_start, _text_end+xram_size, data_size);
    memset(_bss_start, 0, bss_size);

    default_start();
}

/* interrupt vectors */
void default_handler(void){
    while (1){}
}
void nmi_handler(void);
void hardfault_handler(void);
void memmgt_handler(void);
void busfault_handler(void);
void usagefault_handler(void);
void svc_handler(void);
void debugmon_handler(void);
void pendsv_handler(void);
void systick_handler(void);


/* vector table */
void* _vectors[] __attribute((section(".vectors"))) = {
    _stack,
    _reset,
    nmi_handler,
    hardfault_handler,
    hardfault_handler,
    hardfault_handler,
    hardfault_handler,
    0,
    0,
    0,
    0,
    svc_handler,
    debugmon_handler,
    0,
    pendsv_handler,
    systick_handler
};
