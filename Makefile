MCU     = attiny85
F_CPU   = 16000000UL

CC      = avr-gcc
OBJCOPY = avr-objcopy

CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -I ./src/learning -I /usr/local/include
LDFLAGS = 

SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -type f -name '*.c')
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
	# alterar conforme seu programador / porta
	avrdude -c <programmer> -p $(MCU) -U flash:w:$(TARGET).hex:i

.PHONY: all clean flash
