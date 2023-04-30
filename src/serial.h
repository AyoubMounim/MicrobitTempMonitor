
#ifndef SERIAL
#define SERIAL

#include <stdint.h>
#include "macros.h"


#define UARTE0_BASE _BASE(0x40002000)

/* tasks */
#define UARTE0_STARTRX _REG(unsigned, 0x40002000)
#define UARTE0_STOPRX  _REG(unsigned, 0x40002004)
#define UARTE0_STARTTX _REG(unsigned, 0x40002008)
#define UARTE0_STOPTX _REG(unsigned, 0x4000200C)
#define UARTE0_FLUSHRX _REG(unsigned, 0x4000202C)

/* events */
#define UARTE0_CTS _REG(unsigned, 0x40002100)
#define UARTE0_NTCS _REG(unsigned, 0x40002104)
#define UARTE0_RXDRDY _REG(unsigned, 0x40002108)
#define UARTE0_ENDRX _REG(unsigned, 0x40002110)
#define UARTE0_TXDRDY _REG(unsigned, 0x4000211C)
#define UARTE0_ENDTX _REG(unsigned, 0x40002120)
#define UARTE0_ERROR _REG(unsigned, 0x40002124)
#define UARTE0_RXTO _REG(unsigned, 0x40002144)
#define UARTE0_RXSTARTED _REG(unsigned, 0x4000214C)
#define UARTE0_TXSTARTED _REG(unsigned, 0x40002150)
#define UARTE0_TXSTOPPED _REG(unsigned, 0x40002158)
#define UARTE0_SHORTS _REG(unsigned, 0x40002200)

/* interrupts */
#define UARTE0_INTEN _REG(unsigned, 0x40002300)
#define UARTE0_INTENSET _REG(unsigned, 0x40002304)
#define UARTE0_INTENCLR _REG(unsigned, 0x40002308)
#define UARTE0_ERRORSRC _REG(unsigned, 0x40002480)

/* registers */
#define UARTE0_ENABLE _REG(unsigned, 0x40002500)
#define UARTE0_PSELRTS _REG(unsigned, 0x40002508)
#define UARTE0_PSELTXD _REG(unsigned, 0x4000250C)
#define UARTE0_PSELCTS _REG(unsigned, 0x40002510)
#define UARTE0_PSELRXD _REG(unsigned, 0x40002514)
#define UARTE0_BAUDRATE _REG(unsigned, 0x40002524)
#define UARTE0_RXD _REG(unsigned, 0x40002534)
#define UARTE0_RXDMAXCNT _REG(unsigned, 0x40002538)
#define UARTE0_RXDAMOUNNT _REG(unsigned, 0x4000253C)
#define UARTE0_TXD _REG(unsigned, 0x40002544)
#define UARTE0_TXDMAXCNT _REG(unsigned, 0x40002548)
#define UARTE0_TXDAMOUNNT _REG(unsigned, 0x4000254C)
#define UARTE0_CONFIG _REG(unsigned, 0x4000256C)


enum Parity {
  PARITY_EVEN = 0,
  PARITY_ODD = 1,
  PARITY_NONE = 3
};


enum Baudrate {
  BAUD_9600 = 0x00275000,
  BAUD_115200 = 0x01D60000
};


enum HWFC {
  HWFC_ENABLE = 1,
  HWFC_DISABLE = 0
};


void serial_init(void);
void serial_write_ch(const char* ch);
void serial_write_str(const char buff[]);
void serial_write_int(uint32_t integer);
void serial_input(char buff[10]);
void serial_get_char(char* ch);
void serial_flush();

void set_baudrate(enum Baudrate bdrate);
void set_parity(enum Parity parity);
void set_whfc(enum HWFC hwfc);

#endif