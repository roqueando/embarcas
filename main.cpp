#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "rgb/rgb.h"

#define BAUD 9600

int main()
{
    rgb_init();
    while(true) {
        rgb_color(CYAN);
        turn_on(CYAN);
        _delay_ms(5000);
        turn_off(CYAN);
        _delay_ms(5000);
        turn_on(PURPLE);
        _delay_ms(5000);
        turn_off(PURPLE);
    }
    return 0;
}


