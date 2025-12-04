#pragma once

#include <stdint.h>

typedef struct {
  uint8_t green;
  uint8_t red;
  uint8_t blue;
  uint8_t purple;
  int count;
} led_blink_t;

void led_array_init(led_blink_t leds);
void change_led_blink(int state);

void led_init(uint8_t port);
void led_blink(uint8_t port);
void led_high(uint8_t port);
void led_low(uint8_t port);
