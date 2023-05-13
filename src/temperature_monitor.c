
#include <stdint.h>
#include "temperature_monitor.h"
#include "serial.h"
#include "clock.h"
#include "temp_sensor.h"
#include "utils.h"


const char start_prompt[] = "start";


void handle_idle(struct Monitor* p_monitor){
  /* char* prompt = "0"; */
  char prompt[10];
  const char idle_msg[] = "Insert prompt (start to begin)\n\r";
  const char wrong_prompt_msg[] = "prompt not found\n\r";
  serial_write_str(idle_msg);
  serial_input(prompt);
  serial_endl();
  if (cmp_string(prompt, start_prompt)){
    p_monitor->current_state = MEASURE;
    serial_endl();
  }
  else {
    serial_write_str(wrong_prompt_msg);
    serial_endl();
  }
  return;
}


void handle_measure(struct Monitor* p_monitor){
  char end_ch[] = "s";
  const char temperature_msg[] = "temperature: ";
  const char unit_msg[] = " C";
  serial_listen_char(end_ch);
  uint32_t temperature = read_temperature();
  serial_write_str(temperature_msg);
  serial_write_int(temperature);
  serial_write_str(unit_msg);
  serial_endl();
  sleep(10);
  if (end_ch[0] == 'c'){
    p_monitor->current_state = IDLE;
    serial_endl();
  }
  return;
}


void handle_state(struct Monitor* p_monitor){
  char test[] = "ghfhgjfhjfg";
  switch (p_monitor->current_state){
    case IDLE:
      serial_write_str(test);
      handle_idle(p_monitor);
      break;
    case MEASURE:
      serial_write_str(test);
      handle_measure(p_monitor);
      break;
  }
  return;
}


void monitor_run(struct Monitor* p_monitor){
  p_monitor->current_state = IDLE;
  const char welcome_msg[] = "Temperature Monitor\n\rUse 'start' to begin, 'c' to stop.\n\r";
  serial_endl();
  serial_write_str(welcome_msg);
  serial_endl();
  while (1){
      handle_state(p_monitor);
    }
  return;
}
