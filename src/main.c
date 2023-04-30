
#include "hardware.h"
#include "macros.h"
#include "serial.h"
#include "temp_sensor.h"
#include "devpins.h"


void delay_loop(unsigned usec){
    unsigned t = usec << 4;
    while (t > 0){
        nop();
        t--;
    }
    return;
}


void blink(int n_times){
    int i, k;
    static const unsigned ssod[] = {
        _ROW(ROW1, 0, 1, 0, 1, 0),
        _ROW(ROW3, 1, 0, 1, 0, 1),
        _ROW(ROW5, 0, 1, 0, 1, 0),
    };

    GPIO0_DIR = LED_MASK0;
    GPIO1_DIR = LED_MASK1;

    for (int n = 0; n < n_times; n++){
        for (k = 33; k > 0; k--){
            for (i = 0; i < 6; i += 2){
                GPIO0_OUT = ssod[i];
                GPIO1_OUT = ssod[i+1];
                delay_loop(5000);
            }
        }
        GPIO0_OUT = 0;
        GPIO1_OUT = 0;
        delay_loop(100000);
    }
    return;
}


void main(void){
    serial_init();
    blink(5);
    const char dbg[] = "fino a qui tutto bene\n\r";
    const char title[] = "Testing serial input\n\r";
    const char message[] = "Please input a word\n\r";
    const char new_line[] = "\n\r";
    serial_write_str(title);
    char input[10];

    while (1){
        serial_write_str(message);
        serial_input(input);
        serial_write_str(new_line);
        serial_write_str(input);
        serial_write_str(new_line);
        delay_loop(1000000);
    }
    return;
}
