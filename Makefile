
COLOUR_GREEN = \033[0;32m
COLOUR_RED = \033[0;31m
COLOUR_BLUE = \033[0;34m
NO_COLOR = \033[0m

XCC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -c -g -Wall -nostdlib -lgcc -ffreestanding
LD = arm-none-eabi-ld
LSCRIPT = nRF52833.ld
LDFLAGS = -T ../$(SRCDIR)/$(LSCRIPT)
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
.PHONY: clean

app.hex: app.elf
	@echo "$(COLOUR_BLUE)producing hex file...$(NO_COLOR)"
	@cd ./$(BUILDDIR) && $(OBJCOPY) $^ $@
	@echo "$(COLOUR_GREEN)done$(NO_COLOR)"

app.elf: $(OBJLIST)
	@echo "$(COLOUR_BLUE)linking object files...$(NO_COLOR)"
	@cd ./$(BUILDDIR) && $(LD) $(LDFLAGS) -o $@ $(OBJLIST)

$(OBJLIST): src/$(subst .o,.c,$@)
	@echo "$(COLOUR_BLUE)compiling object files...$(NO_COLOR)"
	@$(XCC) $(CFLAGS) -o $(BUILDDIR)/$@ src/$(subst .o,.c,$@)

clean: 
	@$(RM) $(BUILDDIR)/*.o $(BUILDDIR)/*.elf $(BUILDDIR)/*.hex
