
all: build

build:
	@mkdir -p build
	@cd build && cmake -S .. -B . && make

clean:
	@sudo rm build/*.elf build/*.hex