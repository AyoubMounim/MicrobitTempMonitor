
#include "temperature_monitor.h"
#include "serial.h"
#include "clock.h"
#include "temp_sensor.h"
#include "utils.h"


const char start_prompt[] = "start";


void handle_idle(struct Monitor* p_monitor){
  char prompt[10];
  const char idle_msg[] = "Insert prompt\n\r";
  serial_write_str(idle_msg);
  serial_input(prompt);
  serial_endl();
  if (cmp_string(prompt, start_prompt)){
    p_monitor->current_state = MEASURE;
  }
  return;
}


void handle_measure(struct Monitor* p_monitor){
  char end_ch[1];
  serial_listen_char(end_ch);
  uint32_t temperature = read_temperature();
  serial_write_int(temperature);
  serial_endl();
  sleep(10);
  if (end_ch[0] == 'c'){
    p_monitor->current_state = IDLE;
  }
  return;
}


void handle_state(struct Monitor* p_monitor){
  switch (p_monitor->current_state){
    case IDLE:
      handle_idle(p_monitor);
      break;
    case MEASURE:
      handle_measure(p_monitor);
      break;
  }
  return;
}


void monitor_run(struct Monitor* p_monitor){
  p_monitor->current_state = IDLE;
  const char welcome_msg[] = "welcome\n\r";
  serial_write_str(welcome_msg);
  while (1){
      handle_state(p_monitor);
    }
  return;
}