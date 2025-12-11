#include "button.h"
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include "io.h"

void button_init(uint8_t port) {
  cli();
  bitclr(DDRB, port);
  bitset(PINB, PINB1);

  bitset(MCUCR, ISC01);
  bitset(GIMSK, PCIE);
  bitset(PCMSK, PCINT1);

  GIFR = (1<<PCIF);
  sei();
}

int button_pressed(uint8_t port) {
  return bittst(PINB, PINB1) != 0;
}

ISR(PCINT0_vect) {
  if (!button_pressed(PINB1)) {
    bitflp(PORTB, PB3);
  }
}

