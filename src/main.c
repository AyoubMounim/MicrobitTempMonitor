
#include "macros.h"
#include "serial.h"
#include "temperature_monitor.h"
#include "clock.h"


void main(void){
    serial_init();
    serial_endl();
    serial_write_str("Testing temperature application\n\r");

    struct Monitor monitor;
    monitor_run(&monitor);

    while (1){}
    return;
}
