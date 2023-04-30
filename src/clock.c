
#include "clock.h"


void sleep(unsigned usec){
    uint32_t t = usec << 20;
    while (t > 0){
        nop();
        t--;
    }
    return;
}