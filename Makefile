MCU     = attiny85
F_CPU   = 16000000UL
BAUD		= 9600

CC      = avr-gcc
OBJCOPY = avr-objcopy

CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -I /usr/local/include -I /usr/lib/avr/include -I ./include
LDFLAGS = 
PROGRAMMER_TYPE = micronucleus

SRC_DIR = src
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/uart/uart.c $(SRC_DIR)/usi/i2c.c $(SRC_DIR)/usi/spi.c $(SRC_DIR)/ssd1780/ssd1780.c $(SRC_DIR)/adc/adc.c $(SRC_DIR)/usi/spi.c $(SRC_DIR)/eeprom/eeprom.c $(SRC_DIR)/gpio/gpio.c $(SRC_DIR)/power/power.c $(SRC_DIR)/timer/timer0.c
OBJ     = $(SRC:.c=.o)

TARGET  = embarcas

all: $(TARGET).hex

$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

clean:
	rm -f $(TARGET).elf $(TARGET).hex $(SRC_DIR)/*.o

flash: $(TARGET).hex
	avrdude -c $(PROGRAMMER_TYPE) -p t85 -x wait -V -U flash:w:$(TARGET).hex:i

.PHONY: all clean flash
