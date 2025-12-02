#pragma once

//#include <avr/io_atmega328p.h>
#include <avr/iotnx5.h>
#include <stdint.h>

//#define bitset(arg, bit) (arg |= 1<<bit)
//#define bitclr(arg, bit) (arg &= ~(1<<bit))

#define BIT_SET(REG, BIT)    ((REG) |= (1 << (BIT)))
#define BIT_CLEAR(REG, BIT)  ((REG) &= ~(1 << (BIT)))
#define BIT_TOGGLE(REG, BIT) ((REG) ^= (1 << (BIT)))
#define BIT_CHECK(REG, BIT)  ((REG) &  (1 << (BIT)))

//uint8_t bitset(volatile uint8_t arg, uint8_t bit);
//uint8_t bitclr(volatile uint8_t arg, uint8_t bit);
//uint8_t bitflp(volatile uint8_t arg, uint8_t bit);
//uint8_t bittst(volatile uint8_t arg, uint8_t bit);

enum pin_mode {
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
    enum pin_mode direction;
    uint8_t pin;
    enum available_port choosen_port;
};

struct pin_config {
    uint8_t pin;
    enum pin_mode m;
};


/**
 * set the bit in desired pin
 * @param {pin_config} pin configuration that you want to set
 * @param {pin_state} state: the pin state if is high or low
 * @returns void
 */
void digital_write(struct port p, enum pin_state state);
int digital_read(struct port p);

/*
 * configure a port setting your direction within correct port
 */
void set_port_direction(struct port p);
void write_port(uint8_t value, enum available_port p);
void debug_pin(struct port p);

void delay_micro(int a);
void delay_mili(int a);


