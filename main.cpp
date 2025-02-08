#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "io/io.h"
#include "ssd/ssd.h"
#include "shift_register/shift_register.h"

#define BAUD 9600


int main()
{
    int time;

    ssd_init();

    while(true) {
        ssd_digit(0, 0);
        ssd_digit(1, 1);
        ssd_digit(2, 2);
        ssd_digit(3, 3);

        ssd_update();
        for(time = 0; time < 1000; time++);
    }
    return 0;
}


