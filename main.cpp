#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "io/io.h"
#include "ssd/ssd.h"
#include "shift_register/shift_register.h"

#define BAUD 9600

#define D1_PIN {mode::OUTPUT, 1, available_port::D}

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

int main()
{
    int oldValue, t;

    port p0 = {mode::INPUT, 0, available_port::D};
    set_port_direction({mode::INPUT, 0, available_port::D});
    set_port_direction(D1_PIN);
    oldValue = digital_read(p0);

    while(true) {
        /* BOUNCING
        if(oldValue != digital_read(p0)) {
            oldValue = digital_read(p0);
            digital_write(D1_PIN, pin_state::HIGH);
            for(t=0; t<100; t++) {
                if(oldValue != digital_read(p0)) {
                    t = 0;
                }
            }
        }
        */
    }
    return 0;
}


