#include <avr/io.h>
#include "learning/io.h"
#include "learning/led.h"
#include "learning/timer.h"
#include "learning/button.h"
#include <avr/interrupt.h>
#include <stdint.h>

#include <simavr/avr/avr_mcu_section.h>

// this is for VCD
const struct avr_mmcu_vcd_trace_t _mytrace[] _MMCU_ = {
    { AVR_MCU_VCD_SYMBOL("PORTB"), .what = (void*)&PORTB },
    { AVR_MCU_VCD_SYMBOL("TCCR0B"), .what = (void*)&TCCR0B },
    { AVR_MCU_VCD_SYMBOL("TCNT0"),  .what = (void*)&TCNT0 },
};

volatile static uint32_t ms_counter = 0;

uint32_t last_time = 0;

int main() {
  timer_init();

  led_init(PB2);

  while (1) {
    uint32_t current_time = timer();

    if ((current_time - last_time) >= 1000) {
      bitflp(PORTB, PB2);
      last_time = current_time;
    }
  }
  /*
  sei();
  timer_init();

  led_init(PB2);
  led_init(PB3);
  led_init(PB5);
  led_init(PB4);
  //button_init(DDB1);

  while (1) {
    uint32_t current_time = timer();
    if (bittst(TIFR, OCF0A) != 0) {
      bitset(PORTB, PB3);
    }

    if ((current_time - last_time) >= 1000) {
      bitset(PORTB, PB2);
      last_time = current_time;
    }

    bitclr(PORTB, PB3);
    bitclr(PORTB, PB5);
    bitclr(PORTB, PB4);
    change_led_blink(leds.count);

    if (!button_pressed(PINB1)) {
      leds.count++;
    }

    if (leds.count > 3) {
      leds.count = 0;
    }
  }

*/
  return 0;
}
