#include "shift_register.h"
#include "../io/io.h"
#include <util/delay.h>

// B0
#define SO_DATA_PIN {mode::OUTPUT, 0, available_port::B}
#define SO_CLK_PIN {mode::OUTPUT, 1, available_port::B}
#define SO_EN_PIN {mode::OUTPUT, 2, available_port::B}



#define D0_PIN {mode::OUTPUT, 0, available_port::D}
#define D1_PIN {mode::OUTPUT, 1, available_port::D}
#define D2_PIN {mode::OUTPUT, 2, available_port::D}
#define D3_PIN {mode::OUTPUT, 3, available_port::D}


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

    // bit 6
    digital_write(SO_DATA_PIN, pin_state::LOW);
    pulse_clock();

    digital_write(SO_DATA_PIN, pin_state::HIGH);
    pulse_clock();

    digital_write(SO_DATA_PIN, pin_state::HIGH);
    pulse_clock();

    digital_write(SO_DATA_PIN, pin_state::HIGH);
    pulse_clock();

    digital_write(SO_DATA_PIN, pin_state::HIGH);
    pulse_clock();

    digital_write(SO_DATA_PIN, pin_state::HIGH);
    pulse_clock();

    pulse_enable();

    /*
    for (int i = 0; i < 8; i++) {
        // Start data pin send
        //digital_write(D0_PIN, pin_state::HIGH);
        _delay_ms(10000);
        digital_write(SO_DATA_PIN, value & 1);
        //digital_write(D0_PIN, pin_state::LOW);
        // END

        // Start pulse clock
        //digital_write(D1_PIN, pin_state::HIGH);
        _delay_ms(10000);
        pulse_clock();
        //digital_write(D1_PIN, pin_state::LOW);
        // END

        //digital_write(D2_PIN, pin_state::HIGH);
        _delay_ms(10000);
        value <<= 1;
        //digital_write(D2_PIN, pin_state::LOW);
    }
    */
    //pulse_enable();
    //digital_write(D3_PIN, pin_state::HIGH);
    //_delay_ms(10000);
    //digital_write(D3_PIN, pin_state::LOW);
}
