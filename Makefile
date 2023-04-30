
XCC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -c -g -Wall -nostdlib -lgcc
LD = arm-none-eabi-ld
LDFLAGS = 
LSCRIPT = src/nRF52833.ld
OBJCOPY = arm-none-eabi-objcopy -O ihex

SRCDIR = src
BUILDDIR = build
OBJLIST = startup.o main.o serial.o temp_sensor.o clock.o temperature_monitor.o utils.o


all: app.hex

app.hex: app.elf
	$(OBJCOPY) app.elf $@

app.elf: $(LSCRIPT) $(OBJLIST)
	$(LD) $(LDFLAGS) -T $(LSCRIPT) -o $@ $(OBJLIST)

$(OBJLIST): src/*.c
	$(XCC) $(CFLAGS) src/*.c

clean: 
	@sudo rm *.o *.elf *.hex
