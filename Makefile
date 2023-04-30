
XCC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -c -g -Wall -nostdlib -lgcc
LD = arm-none-eabi-ld
LSCRIPT = src/nRF52833.ld
LDFLAGS = -T $(LSCRIPT)
OBJCOPY = arm-none-eabi-objcopy -O ihex

SRCDIR = src
BUILDDIR = build
OBJLIST = startup.o main.o serial.o temp_sensor.o clock.o temperature_monitor.o utils.o

vpath %.c $(SRCDIR)
vpath %.h $(SRCDIR)
vpath %.o $(BUILDDIR)
vpath %.elf $(BUILDDIR)
vpath %.hex $(BUILDDIR)


all: app.hex

app.hex: app.elf
	$(OBJCOPY) $^ $(BUILDDIR)/$@

app.elf: $(OBJLIST)
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/$@ $(BUILDDIR)/$(OBJLIST)

$(OBJLIST): src/$(subst .o,.c,$@)
	$(XCC) $(CFLAGS) -o $(BUILDDIR)/$@ src/$(subst .o,.c,$@)

clean: 
	@sudo rm $(BUILDDIR)/*.o $(BUILDDIR)/*.elf $(BUILDDIR)/*.hex
