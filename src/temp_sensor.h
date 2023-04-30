
#ifndef TEMP_SENSOR
#define TEMP_SENSOR

#include <stdint.h>
#include "macros.h"


#define TEMP_BASE 0x4000C000

/* tasks */
#define TEMP_START REG(uint32_t, TEMP_BASE, 0x0)
#define TEMP_STOP REG(uint32_t, TEMP_BASE, 0x004)

/* events */
#define TEMP_DATARDY REG(uint32_t, TEMP_BASE,  0x100)

/* interrupts */
#define TEMP_INTENSET REG(uint32_t, TEMP_BASE, 0x304)
#define TEMP_INTENCLR REG(uint32_t, TEMP_BASE, 0x308)

/* registers */
#define TEMP_VALUE REG(uint32_t, TEMP_BASE, 0x508)
#define TEMP_A0 REG(uint32_t, TEMP_BASE, 0x520)
#define TEMP_A1 REG(uint32_t, TEMP_BASE, 0x524)
#define TEMP_A2 REG(uint32_t, TEMP_BASE, 0x528)
#define TEMP_A3 REG(uint32_t, TEMP_BASE, 0x52C)
#define TEMP_A4 REG(uint32_t, TEMP_BASE, 0x530)
#define TEMP_A5 REG(uint32_t, TEMP_BASE, 0x534)
#define TEMP_B0 REG(uint32_t, TEMP_BASE, 0x540)
#define TEMP_B1 REG(uint32_t, TEMP_BASE, 0x544)
#define TEMP_B2 REG(uint32_t, TEMP_BASE, 0x548)
#define TEMP_B3 REG(uint32_t, TEMP_BASE, 0x54C)
#define TEMP_B4 REG(uint32_t, TEMP_BASE, 0x550)
#define TEMP_B5 REG(uint32_t, TEMP_BASE, 0x554)
#define TEMP_T0 REG(uint32_t, TEMP_BASE, 0x560)
#define TEMP_T1 REG(uint32_t, TEMP_BASE, 0x564)
#define TEMP_T2 REG(uint32_t, TEMP_BASE, 0x568)
#define TEMP_T3 REG(uint32_t, TEMP_BASE, 0x56C)
#define TEMP_T4 REG(uint32_t, TEMP_BASE, 0x570)


uint32_t read_temperature(void);


#endif