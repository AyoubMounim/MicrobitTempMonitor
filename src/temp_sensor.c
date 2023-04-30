
#include "temp_sensor.h"


void temp_reset(void){
  TEMP_DATARDY = 0;
  return;
}


void temp_trigger(void){
  TEMP_START = 1;
  return;
}


void temp_block(void){
  while (!TEMP_DATARDY){}
  return;
}


uint32_t read_value(void){
  return TEMP_VALUE;
}


uint32_t temp_from_value(uint32_t value){
  return value;
}


uint32_t read_temperature(void){
  temp_reset();
  temp_trigger();
  temp_block();
  uint32_t temp_value = read_value();
  uint32_t temperature = temp_from_value(temp_value);
  return temperature;
}
