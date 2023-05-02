
# Temperature Monitor

The final executable of this repo is a simple temperature monitor that runs on
the micro:bit board or on any nRF52833 SoC with minor adjustments (you only need
to change the definition of the UARTE Tx an Rx pins found in "devpins.h").

The monitor is controlled via serial input and it uses serial comunication for 
output as well. You start the monitor by givin the "start" command. Once started,
the monitor outputs the temperature measured by the nRF52833's integrated temperature 
sensor at regular time intervals (roughly once every 2 seconds). Once started you
can stop the application by pressing the "c" character on your keyboard.