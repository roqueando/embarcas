#include "io.h"

void debug_pin(port p)
{
    set_port_direction(p);
    digital_write(p, pin_state::HIGH);
}

void set_port_direction(port p)
{
    switch (p.choosen_port) {
        case available_port::D:
            p.direction == mode::OUTPUT ? bitset(DDRD, p.pin) : bitclr(DDRD, p.pin);
            break;

        case available_port::C:
            p.direction == mode::OUTPUT ? bitset(DDRC, p.pin) : bitclr(DDRC, p.pin);
            break;

        case available_port::B:
            p.direction == mode::OUTPUT ? bitset(DDRB, p.pin) : bitclr(DDRB, p.pin);
            break;
    }
}

void digital_write(port p, uint8_t state)
{
    if (p.direction == mode::OUTPUT) {
        switch (p.choosen_port) {
            case available_port::D:
                state == pin_state::HIGH ? bitset(PORTD, p.pin) : bitclr(PORTD, p.pin);
                break;

            case available_port::C:
                state == pin_state::HIGH ? bitset(PORTC, p.pin) : bitclr(PORTC, p.pin);
                break;

            case available_port::B:
                state == pin_state::HIGH ? bitset(PORTB, p.pin) : bitclr(PORTB, p.pin);
                break;
        }
    }
    // TODO: contemplate the INPUT data
}

void write_port(uint8_t value, available_port p)
{
    switch (p) {
        case available_port::D:
            PORTD = value;
            break;

        case available_port::C:
            PORTC = value;
            break;

        case available_port::B:
            PORTB = value;
            break;
    }
}
