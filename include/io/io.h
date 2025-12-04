#pragma once

//#include <avr/io_atmega328p.h>
//#include <stdint.h>

#define bitset(arg,bit) ((arg) |= (1<<(bit)))
#define bitclr(arg,bit) ((arg) &= ~(1<<(bit)))
#define bitflp(arg,bit) ((arg) ^= (1<<(bit)))
#define bittst(arg,bit) ((arg) & (1<<(bit)))
