build:
	@avr-g++ -mmcu=atmega328p -o main.elf main.cpp io/io.cpp rgb/rgb.cpp
	@avr-objcopy -O ihex -R .eeprom main.elf main.hex
	@rm main.elf

build-test:
	@gcc test.c -o test && ./test

flash:
	@avrdude -c arduino -p atmega328p -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex:i
