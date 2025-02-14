TARGET = embarcas
BUILDDIR = build

build: $(BUILDDIR)/Makefile
	@cmake --build build/debug


$(BUILDDIR)/Makefile:
	@cmake -DCMAKE_BUILD_TYPE=Debug -B build/debug

build-test:
	@gcc test.c -o test && ./test

flash:
	@avrdude -c arduino -p atmega328p -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex:i

.PHONY: build
