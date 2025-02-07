#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "io/io.h"
//#include "ssd/ssd.h"
#include "shift_register/shift_register.h"

#define BAUD 9600


int main()
{
    unsigned int time, count = 0;

    set_port_direction({mode::OUTPUT, 0, available_port::D});
    set_port_direction({mode::OUTPUT, 1, available_port::D});
    set_port_direction({mode::OUTPUT, 2, available_port::D});
    set_port_direction({mode::OUTPUT, 3, available_port::D});

    so_init();
    //ssd_init();
    while(true) {
        so_write(0x3F);
        for(time = 0; time < 1000; time++);
        /*
        count++;
        ssd_digit(0, (count) % 10);
        ssd_digit(1, (count / 10) % 10);
        ssd_digit(2, (count / 100) % 10);
        ssd_digit(3, (count / 1000) % 10);
        ssd_update();
        for(time=0; time < 1000; time++);
        //digital_write({mode::OUTPUT, 0, available_port::D}, pin_state::HIGH);
        */
    }
    return 0;
}


