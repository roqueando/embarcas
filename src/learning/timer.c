#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#include <stdint.h>


void timer_init() {
  cli();
  //1. CTC mode => clear timer on compare mode
  TCCR0A = (1 << WGM01);
  bitset(TCCR0A, COM0A0);

  bitset(DDRB, PB0);

  // compares
  OCR0A = 200; // custom overflow flag
  OCR0B = 200;

  // reset counter  
  TCNT0 = 0;

  // clean all pending flags
  TIFR = (1<<OCF0A) | (1<<OCF0B) | (1<<TOV0);

  //2. prescalers -> setting up 64 prescaler
  TCCR0B |= (1 << CS01) | (1<<CS00);

  //3. calling interrupts

  // enabling the interrupt
  TIMSK = (1<<OCIE0A);
  TIMSK = (1<<OCIE0B);

  // activate global interrupts
  sei();
}

ISR(TIMER0_COMPA_vect) {
  OCR0A = 160;
  TCNT0 = 0;
}

ISR(TIMER0_COMPB_vect) {
  OCR0B = 40;
}

