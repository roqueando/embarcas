#include "io/io.h"
#include <learning/led.h>
#include <learning/button.h>
#include <avr/iotnx5.h>

int main() {
  led_blink_t leds = {
      .red = PB2, .green = PB5, .blue = PB3, .purple = PB4, .count = 0};

  led_array_init(leds);
  button_init(DDB1);

  while (1) {
    change_led_blink(leds.count);

    if (!button_pressed(PINB1)) {
      leds.count++;
    }

    if (leds.count > 3) {
      leds.count = 0;
    }
  }

  return 0;
}
