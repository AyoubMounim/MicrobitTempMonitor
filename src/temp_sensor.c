
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
  return TEMP_VALUE/4;
}


uint32_t linear_correction(uint32_t value){
  uint32_t temperature;
  if (value <= TEMP_T0){
    temperature = TEMP_A0*value + TEMP_B0;
    return temperature;
  }
  else if (value <= TEMP_T1){
    temperature = TEMP_A1*value + TEMP_B1;
    return temperature;
  }
  else if (value <= TEMP_T2){
    temperature = TEMP_A2*value + TEMP_B2;
    return temperature;
  }
  else if (value <= TEMP_T3){
    temperature = TEMP_A3*value + TEMP_B3;
    return temperature;
  }
  else if (value <= TEMP_T4){
    temperature = TEMP_A4*value + TEMP_B4;
    return temperature;
  }
  else {
    temperature = TEMP_A5*value + TEMP_B5;
    return temperature;
  }
}


uint32_t read_temperature(void){
  temp_reset();
  temp_trigger();
  temp_block();
  uint32_t temperature = read_value();
  return temperature;
}
