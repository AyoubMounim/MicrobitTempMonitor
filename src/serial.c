
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


void set_hwfc(enum HWFC hwfc){
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


void rx_reset(){
  UARTE0_RXDRDY = 0;
  UARTE0_RXTO = 0;
  UARTE0_STARTRX = 0;
  UARTE0_ENDRX = 0;
  return;
}


void set_buff_size(uint32_t size){
  UARTE0_TXDMAXCNT = size;
  return;
}


void write_str(const char* str){
  UARTE0_TXD = (uint32_t) str;
  return;
}


void serial_block(){
  while (!UARTE0_ENDTX){}
  return;
}


uint32_t str_size(const char* str){
  uint32_t len = 0;
  while (*(str + len) != '\0'){
    len++;
  }
  return len;
}


uint8_t number_of_digits(uint32_t integer, uint8_t base){
  uint8_t n_digits = 0;
  do {
      n_digits++; 
      integer /= base;
  } while (integer > 0);
  return n_digits;
}


void rx_read(char* ch){
  UARTE0_RXDMAXCNT = 1;
  UARTE0_RXD = (uint32_t) ch;
  UARTE0_STARTRX = 1;
  return;
}


void rx_block(){
  while (!UARTE0_ENDRX || !UARTE0_RXDRDY){}
  return;
}


void rx_stop(){
  UARTE0_STOPRX = 1;
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
  write_str(ch);
  trigger_tx();
  serial_block();
  return;
}


void serial_write_str(const char* str){
  tx_reset();
  uint32_t buff_size = str_size(str);
  set_buff_size(buff_size);
  char str_array[buff_size];
  for (int i=0; i<buff_size; i++){
    str_array[i] = *(str + i);
  }
  write_str(str_array);
  trigger_tx();
  serial_block();
  return;
}


void serial_write_int(uint32_t integer, uint8_t base){
  static const char dec[] = "0123456789ABCDEF";
  uint8_t n_digits = number_of_digits(integer, base);
  char digits[n_digits+1];
  digits[n_digits] = '\0';
  while (--n_digits >= 0){
      digits[n_digits] = dec[integer%base];
      integer /= base;
  }
  serial_write_str(digits);
  return;
}


void serial_get_char(char* ch){
  rx_reset();
  rx_read(ch);
  rx_block();
  rx_stop();
  return;
}


void serial_listen_char(char* ch){
  rx_reset();
  rx_read(ch);
  return;
}


void serial_flush(){
  UARTE0_FLUSHRX = 1;
  return;
}


void serial_input(char* input_array){
  char rx_buff[1];
  int i = 0;
  while (i < MAX_INPUT_LEN){
    serial_get_char(rx_buff);
    if (*rx_buff == '\r'){
      input_array[i] = '\0';
      /* serial_flush(); */
      return;
    }
    serial_write_ch(rx_buff);
    input_array[i] = rx_buff[0];
    i++;
  }
  return;
}


void serial_endl(){
  serial_write_str("\n\r");
  return;
}

