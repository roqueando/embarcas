#include <learning/button.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/iotnx5.h>
#include <io/io.h>

void button_init(uint8_t port) {
  bitclr(DDRB, port);
  bitset(PINB, PINB1);
}

int button_pressed(uint8_t port) {
  return (bittst(PINB, port) != 0);
}
