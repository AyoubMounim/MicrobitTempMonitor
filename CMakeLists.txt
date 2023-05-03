
cmake_minimum_required(VERSION 3.0)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING TRUE)

project(monitor_temp C)

set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_OBJCOPY  "arm-none-eabi-objcopy")

file(GLOB LINKSCRIPT "src/nRF52833.ld")
set(SRCLIST src/startup.c src/clock.c src/main.c src/serial.c src/temp_sensor.c src/temperature_monitor.c src/utils.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostartfiles -nostdlib -g -Wall -mcpu=cortex-m4 -mthumb -ffreestanding")
set(CMAKE_EXE_LINKER_FLAGS "-T ${LINKSCRIPT}")

add_executable(app ${SRCLIST})
set_target_properties(app PROPERTIES OUTPUT_NAME "app.elf")

add_custom_command(TARGET app POST_BUILD COMMAND ${CMAKE_OBJCOPY} -O ihex app.elf app.hex COMMENT "Converting .elf file to .hex file")
