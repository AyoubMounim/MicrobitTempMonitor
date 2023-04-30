
#ifndef CLOCK
#define CLOCK

#include <stdint.h>
#include "macros.h"


#define CLOCK_BASE           _BASE(0x40000000)
#define CLOCK_HFCLKSTART     _REG(unsigned, 0x40000000)
#define CLOCK_LFCLKSTART     _REG(unsigned, 0x40000008)
#define CLOCK_HFCLKSTARTED   _REG(unsigned, 0x40000100)
#define CLOCK_LFCLKSTARTED   _REG(unsigned, 0x40000104)
#define CLOCK_LFCLKSRC       _REG(unsigned, 0x40000518)
#define CLOCK_LFCLKRC_RC     0
#define CLOCK_XTALFREQ_16MHz 0xFF


void sleep(unsigned usec);

#endif