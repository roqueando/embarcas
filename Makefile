TARGET = embarcas
BUILDDIR = build

build: $(BUILDDIR)/Makefile
	@cmake --build build/debug


$(BUILDDIR)/Makefile:
	@cmake -DCMAKE_BUILD_TYPE=Debug -B build/debug

build-test:
	@gcc test.c -o test && ./test

flash: build
	@avrdude -c arduino -p atmega328p -P /dev/$(PORT) -b 115200 -U flash:w:build/debug/embarcas.hex:i

.PHONY: build flash
