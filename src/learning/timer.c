#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#include <stdint.h>

volatile static uint32_t ms_counter = 0;

void timer_init() {
  cli();
  //1. CTC mode => clear timer on compare mode
  TCCR0A = (1 << WGM00);

  // compares
  OCR0A = 249; // custom overflow flag
  OCR0B = 0xFF;

  // reset counter  
  TCNT0 = 0;

  // clean all pending flags
  TIFR = (1<<OCF0A) | (1<<OCF0B) | (1<<TOV0);

  //2. prescalers -> setting up 64 prescaler
  TCCR0B |= (1 << CS01) | (1<<CS00);

  //3. calling interrupts

  // enabling the interrupt
  TIMSK = (1<<OCIE0A);

  // activate global interrupts
  sei();
}

ISR(TIMER0_COMPA_vect) {
  ms_counter++;
}

uint32_t timer() {
  uint32_t time;
  cli(); // stop all interrupts

  time = ms_counter;

  sei(); // start all interrupts
  return time;  
}

