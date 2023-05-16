
#ifndef TEMPERATURE_MONITOR
#define TEMPERATURE_MONITOR


typedef enum {
  IDLE = 0,
  MEASURE = 1,
} State;


struct Monitor {
  State current_state;
};


void handle_state(struct Monitor* p_monitor);

void monitor_run(struct Monitor* p_monitor);

#endif
