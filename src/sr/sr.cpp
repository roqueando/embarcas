#include <sr/sr.hpp>
#include <io/io.hpp>

#define SO_DATA_PIN {pin_mode::OUTPUT, 2, available_port::D}
#define SO_CLK_PIN {pin_mode::OUTPUT, 0, available_port::D}
#define SO_EN_PIN {pin_mode::OUTPUT, 1, available_port::D}


void sr_init()
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

void sr_write(int value)
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
