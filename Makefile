TARGET = embarcas
BUILDDIR = build
MCU = attiny85

build: $(BUILDDIR)/Makefile
	@cmake --build build/debug 


$(BUILDDIR)/Makefile:
	@cmake -DCMAKE_BUILD_TYPE=Debug -B build/debug -S . -DCMAKE_TOOLCHAIN_FILE=cmake/avr-toolchain.cmake

build-test:
	@gcc test.c -o test && ./test

flash: build
	@avrdude -c arduino -p $(MCU) -P /dev/$(PORT) -b 115200 -U flash:w:build/debug/embarcas.hex:i

.PHONY: build flash
