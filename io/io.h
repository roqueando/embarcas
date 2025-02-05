#ifndef IO_H
#define IO_H

#include <avr/io.h>
#include <stdint.h>

#define bitset(arg, bit) (arg |= (1<<bit))
#define bitclr(arg, bit) (arg &= ~(1<<bit))
#define bitflp(arg, bit) (arg ^= (1<<bit))
#define bittst(arg, bit) (arg & (1<<bit))

#define DEBUG_PIN PD3

enum mode {
    INPUT,
    OUTPUT
};

enum pin_state {
    LOW,
    HIGH
};

enum available_port {
    D,
    C,
    B
};

struct port
{
    mode direction;
    uint8_t pin;
    available_port choosen_port;
};
// ex: port pd2 = {mode::OUTPUT, 2, 'D'};

struct pin_config {
    uint8_t pin;
    mode m;
};


/*
 * SET_PIN_MODE set the pin mode using bitset and bitclr
 *  @param PORT macro, like PORTD/PORTB/PORTx
 *  @param PIN macro, like PD2 (PORTD bit 2), PD0, PB1, Pxy
 *  @param and a MODE, that will be 0 or 1
 *  @returns void
*/
#define SET_PIN_MODE(PORT, PIN, MODE) ((MODE) == 1 ? (bitset(PORT, PIN)) : (bitclr(PORT, PIN)))

/**
 * set the bit in desired pin
 * @param {pin_config} pin configuration that you want to set
 * @param {pin_state} state: the pin state if is high or low
 * @returns void
 */
void digital_write(port, pin_state);

/*
 * configure a port setting your direction within correct port
 */
void set_port_direction(port);


#endif // IO_H
