
cmake_minimum_required(VERSION 3.22)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING TRUE)

set(CMAKE_C_STANDARD 99)


project(microbit_tests C)

set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE__OBJCOPY "arm-none-eabi-objcopy")

file(GLOB LINKSCRIPT "src/nRF82333.ld")
set(SRCLIST src/startup.c src/main.c src/serial.c src/temp_sensor.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdlib -nostartfiles -g -Wall -mcpu=cortex-m4 -mthumb")
set(CMAKE_EXE_LINKER_FLAGS "-T ${LINKSCRIPT}")

add_executable(test_app ${SRCLIST})
set_target_properties(test_app PROPERTIES OUTPUT_NAME "test_app.elf")
add_custom_command(TARGET test_app POST_BUILD COMMAND ${CMAKE_OBJCOPY} -O ihex test_app.elf test_app.hex)
