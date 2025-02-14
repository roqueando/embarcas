#include <io/io.hpp>

uint8_t bitset(uint8_t arg, uint8_t bit) { return arg |= 1<<bit; }
uint8_t bitclr(uint8_t arg, uint8_t bit) { return arg &= ~(1<<bit); }
uint8_t bitflp(uint8_t arg, uint8_t bit) { return arg ^= 1<<bit; }
uint8_t bittst(uint8_t arg, uint8_t bit) { return arg & 1<<bit; }

void debug_pin(port p)
{
    set_port_direction(p);
    digital_write(p, pin_state::HIGH);
}

void set_port_direction(port p)
{
    switch (p.choosen_port) {
        case available_port::D:
            p.direction == pin_mode::OUTPUT ? bitset(DDRD, p.pin) : bitclr(DDRD, p.pin);
            break;

        case available_port::C:
            p.direction == pin_mode::OUTPUT ? bitset(DDRC, p.pin) : bitclr(DDRC, p.pin);
            break;

        case available_port::B:
            p.direction == pin_mode::OUTPUT ? bitset(DDRB, p.pin) : bitclr(DDRB, p.pin);
            break;
    }
}

void digital_write(port p, pin_state state)
{
    if (p.direction == pin_mode::OUTPUT) {
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
}

int digital_read(port p)
{
    switch(p.choosen_port) {
        case available_port::D:
            return bittst(PIND, p.pin);
        case available_port::C:
            return bittst(PINC, p.pin);
        case available_port::B:
            return bittst(PINB, p.pin);
    }
}

void write_port(uint8_t value, available_port p)
{
    switch (p) {
        case available_port::D:
            bitset(PORTD, value);
            break;

        case available_port::C:
            bitset(PORTC, value);
            break;

        case available_port::B:
            bitset(PORTB, value);
            break;
    }
}
