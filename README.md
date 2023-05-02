
# Temperature Monitor

The final executable of this repo is a simple temperature monitor that runs on
the [micro:bit](https://microbit.org/) board. The source code for application was written entirely from scratch, and it is designed to run on the bare metal, meaning that the application can actually run on any [nRF52833](https://infocenter.nordicsemi.com/pdf/nRF52833_OPS_v0.7.pdf) SoC with minor adjustments (you only need
to change the definition of the UARTE Tx an Rx pins found in "src/devpins.h").
You can build the application by using the make command in the root directory,
and you should find the app.hex file in the build folder.

The monitor is controlled via serial input and it uses serial comunication for 
output as well. You start the monitor by givin the "start" command. Once started,
the monitor outputs the temperature measured by the nRF52833's integrated temperature 
sensor at regular time intervals (roughly once every 2 seconds). Once started you
can stop the application by pressing the "c" character on your keyboard.

![alt text][screen-shot]

The current implementation is a bit hacky and sloppy. There is much room for 
improvement. For instance:
* Interrupt control implementation
* Better implementation of the serial interface
* Implementation of floating point calculations 

## References

* [Spivey's Corner](https://spivey.oriel.ox.ac.uk/corner/Welcome_to_Spivey%27s_Corner)


[screen-shot]: figures/screen.png