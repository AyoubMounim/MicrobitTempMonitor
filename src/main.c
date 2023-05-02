
#include "macros.h"
#include "serial.h"
#include "temperature_monitor.h"
#include "clock.h"


void main(void){
    serial_init();
    /* const char dbg[] = "fino a qui tutto bene\n\r"; */

    const char title[] = "Testing temperature application\n\r";
    serial_endl();
    serial_write_str(title);

    struct Monitor monitor;
    monitor_run(&monitor);

    while (1){}
    return;
}
