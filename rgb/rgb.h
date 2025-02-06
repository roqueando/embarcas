#ifndef RGB_H
#define RGB_H

#include "../io/io.h"

#define OFF 0
#define RED 1
#define GREEN 4
#define BLUE 2

#define YELLOW (RED + GREEN)
#define CYAN (BLUE + GREEN)
#define PURPLE (BLUE + RED)
#define WHITE (RED + GREEN + BLUE)

#define LED_R_PIN 2
#define LED_B_PIN 4
#define LED_G_PIN 3

port get_port(uint8_t pin);
void rgb_init(void);
void rgb_color(int led);
void turn_on(int led);
void turn_off(int led);
void blink_rgb();

#endif // RGB_H
