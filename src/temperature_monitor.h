
#ifndef TEMPERATURE_MONITOR
#define TEMPERATURE_MONITOR

#include <stdint.h>


typedef enum {
  IDLE,
  MEASURE,
} State;


typedef struct Monitor {
  State current_state;
};


void handle_state(struct Monitor* p_monitor);

void monitor_run(struct Monitor* p_monitor);

#endif