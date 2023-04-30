
XCC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -c -g -Wall
LD = arm-none-eabi-ld
LDFLAGS = 
LSCRIPT = src/nRF52833.ld
OBJCOPY = arm-none-eabi-objcopy -O ihex


all: app.hex

app.hex: app.elf
	$(OBJCOPY) app.elf app.hex

app.elf: $(LSCRIPT) startup.o main.o serial.o temp.o
	$(LD) $(LDFLAGS) -T $(LSCRIPT) -o app.elf startup.o main.o serial.o temp.o

startup.o: src/startup.c
	$(XCC) $(CFLAGS) -o startup.o src/startup.c

main.o: src/main.c
	$(XCC) $(CFLAGS) -o main.o src/main.c

serial.o: src/serial.c
	$(XCC) $(CFLAGS) -o serial.o src/serial.c

temp.o: src/temp_sensor.c
	$(XCC) $(CFLAGS) -o temp.o src/temp_sensor.c

clean: 
	sudo rm *.o *.elf *.hex
