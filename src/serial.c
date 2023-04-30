
#include "devpins.h"
#include "serial.h"
#include "macros.h"




void set_baudrate(enum Baudrate bdrate){
  UARTE0_BAUDRATE = bdrate;
  return;
}


void set_parity(enum Parity parity){
  switch (parity){
    case PARITY_NONE:
      SET_FIELD(UARTE0_CONFIG, 1, 3, 0);
      break;
    case PARITY_EVEN:
      SET_FIELD(UARTE0_CONFIG, 1, 3, 7);
      SET_FIELD(UARTE0_CONFIG, 8, 1, 0);
      break;
    case PARITY_ODD:
      SET_FIELD(UARTE0_CONFIG, 1, 3, 7);
      SET_FIELD(UARTE0_CONFIG, 8, 1, 1);
      break;
    default:
      SET_FIELD(UARTE0_CONFIG, 1, 3, 0);
      break;
  }
  return;
}


void set_whfc(enum HWFC hwfc){
  SET_FIELD(UARTE0_CONFIG, 0, 1, hwfc);
  return;
}


void serial_enable(){
  UARTE0_ENABLE = 8;
  return;
}


void serial_disable(){
  UARTE0_ENABLE = 0;
  return;
}


void set_tx_pin(){
  UARTE0_PSELTXD = USB_TX;
  return;
}


void set_rx_pin(){
  UARTE0_PSELRXD = USB_RX;
  return;
}


void trigger_tx(){
  UARTE0_STARTTX = 1;
  return;
}


void trigger_rx(){
  UARTE0_STARTRX = 1;
  return;
}


void tx_reset(){
  UARTE0_TXDRDY = 0;
  UARTE0_STARTTX = 0;
  UARTE0_ENDTX = 0;
  return;
}


void set_buff_size(int size){
  UARTE0_TXDMAXCNT = size;
  return;
}


void write_buffer(const char buff[]){
  UARTE0_TXD = (unsigned) &(buff[0]);
  return;
}


void serial_block(){
  while (!UARTE0_ENDTX){}
  return;
}


int buffer_size(const char buff[]){
  int len = 0;
  while (buff[len] != 0){
    len++;
  }
  return len;
}


void int32_to_char(uint32_t integer, char buff[4]){
  uint32_t val = integer;
  buff[0] = val;
  buff[1] = val >> 8;
  buff[2] = val >> 16;
  buff[3] = val >> 24;
  return;
}


void rx_reset(){
  UARTE0_RXDRDY = 0;
  UARTE0_RXTO = 0;
  UARTE0_STARTRX = 0;
  UARTE0_ENDRX = 0;
  return;
}


void rx_read(char* ch){
  UARTE0_RXDMAXCNT = 1;
  UARTE0_RXD = (unsigned) ch;
  UARTE0_STARTRX = 1;
  return;
}


void rx_block(){
  while (!UARTE0_ENDRX || !UARTE0_RXDRDY){}
  return;
}


void rx_stop(){
  UARTE0_STARTRX = 1;
  return;
}


void serial_init(){
  serial_disable();
  set_baudrate(BAUD_9600);
  set_parity(PARITY_NONE);
  set_tx_pin();
  set_rx_pin();
  serial_enable();
  return;
}


void serial_write_ch(const char* ch){
  tx_reset();
  set_buff_size(1);
  const char buff[] = {*ch};
  write_buffer(buff);
  trigger_tx();
  serial_block();
  return;
}


void serial_write_str(const char buff[]){
  tx_reset();
  int buff_size = buffer_size(buff);
  set_buff_size(buff_size);
  write_buffer(buff);
  trigger_tx();
  serial_block();
  return;
}


void serial_write_int(uint32_t integer){
  char buff[4];
  int32_to_char(integer, buff);
  serial_write_str(buff);
  return;
}


void serial_get_char(char* ch){
  rx_reset();
  rx_read(ch);
  rx_block();
  rx_stop();
  return;
}


void serial_flush(){
  UARTE0_FLUSHRX = 1;
  return;
}


void serial_input(char buff[10]){
  char rx_buff[1];
  int i = 0;
  while (1){
    serial_get_char(rx_buff);
    if (*rx_buff == '\r'){
      buff[i] = '\0';
      return;
    }
    serial_write_ch(rx_buff);
    buff[i] = *rx_buff;
    i++;
  }
  return;
}
