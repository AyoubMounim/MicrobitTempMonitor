
#include "macros.h"
#include "serial.h"
#include "temperature_monitor.h"
#include "clock.h"


void main(void){
    serial_init();
    const char dbg[] = "fino a qui tutto bene\n\r";

    const char title[] = "Testing temperature application\n\r";
    serial_endl();
    serial_write_str(title);

    struct Monitor monitor;
    monitor_run(&monitor);

    const char message[] = "Please input a word\n\r";
    char input[10];
    const char new_line[] = "\n\r";
    while (1){
        serial_write_str(message);
        serial_input(input);
        serial_write_str(new_line);
        serial_write_str(input);
        serial_write_str(new_line);
        sleep(100);
    }
    return;
}
