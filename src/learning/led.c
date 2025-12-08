#include <avr/io.h>
#include "io.h"
#include "led.h"
#include <stdint.h>
#include <util/delay.h>

void led_array_init(led_blink_t leds) {
  led_init(leds.green);
  led_init(leds.red);
  led_init(leds.blue);
  led_init(leds.purple);
}

void change_led_blink(int state) {
    switch (state) {
    case 0:
      led_blink(PB2);
      break;
    case 1:
      led_blink(PB5);
      break;
    case 2:
      led_blink(PB3);
      break;
    case 3:
      led_blink(PB4);
      break;
    }
}

void led_init(uint8_t port) { bitset(DDRB, port); }

void led_blink(uint8_t port) {
  led_high(port);
  _delay_ms(1000); // FIXME: change to our delay
  led_low(port);
  _delay_ms(1000);
}

void led_high(uint8_t port) { bitset(PORTB, port); }
void led_low(uint8_t port) { bitclr(PORTB, port); }
