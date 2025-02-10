#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "io/io.h"
#include "servo/servo.h"

#define BAUD 9600

/*
void four_display_segments()
{
    int time;

    ssd_init();

    while(true) {
        ssd_digit(0, 2);
        ssd_digit(1, 0);
        ssd_digit(2, 2);
        ssd_digit(3, 5);

        ssd_update();
        for(time = 0; time < 1000; time++);
    }
}
*/


int main()
{
    servo_init();
    while(true) {
        turn_clockwise();
        turn_counter_clockwise();
    }
    return 0;
}


