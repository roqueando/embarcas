#include "shift_register.h"
#include "../io/io.h"
#include <util/delay.h>

#define SO_DATA_PIN {mode::OUTPUT, 2, available_port::D}
#define SO_CLK_PIN {mode::OUTPUT, 0, available_port::D}
#define SO_EN_PIN {mode::OUTPUT, 1, available_port::D}


void so_init()
{
    set_port_direction(SO_EN_PIN);
    set_port_direction(SO_DATA_PIN);
    set_port_direction(SO_CLK_PIN);
}

void pulse_enable()
{
    digital_write(SO_EN_PIN, pin_state::HIGH);
    digital_write(SO_EN_PIN, pin_state::LOW);
}

void pulse_clock()
{
    digital_write(SO_CLK_PIN, pin_state::HIGH);
    digital_write(SO_CLK_PIN, pin_state::LOW);
}

void so_write(int value)
{
    digital_write(SO_CLK_PIN, pin_state::LOW);

    for (int i = 0; i < 8; i++) {
        if (value & 0x80) {
            digital_write(SO_DATA_PIN, pin_state::HIGH);
        } else {
            digital_write(SO_DATA_PIN, pin_state::LOW);
        }

        pulse_clock();
        value <<= 1;
    }
    pulse_enable();
}
