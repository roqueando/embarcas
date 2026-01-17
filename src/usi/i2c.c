/**
 * @file usi_i2c.c
 * @brief USI I2C implementation for ATtiny85
 */

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usi/i2c.h"

static uint8_t usi_data;

i2c_t i2c_init(i2c_config_t config) {
    DDRB |= (1 << config.sda_pin);
    DDRB &= ~(1 << config.scl_pin);
    PORTB &= ~((1 << config.sda_pin) | (1 << config.scl_pin));

    USICR = (1 << USIWM1) | (1 << USICS1) | (1 << USIWM0);

    i2c_t i2c = { .config = config };
    return i2c;
}

i2c_status_t i2c_start(i2c_t *i2c) {
    PORTB |= (1 << i2c->config.sda_pin);

    for (uint8_t i = 0; i < 20; i++) {
        _delay_us(1);
    }

    PORTB &= ~(1 << i2c->config.sda_pin);
    return I2C_OK;
}

i2c_status_t i2c_stop(i2c_t *i2c) {
    PORTB &= ~((1 << i2c->config.sda_pin) | (1 << i2c->config.scl_pin));
    return I2C_OK;
}

i2c_status_t i2c_write_byte(i2c_t *i2c, uint8_t data) {
    USIDR = data;

    for (uint8_t i = 0; i < 8; i++) {
        asm volatile("nop");
    }

    return I2C_OK;
}

i2c_status_t i2c_write_byte_wait_ack(i2c_t *i2c, uint8_t data) {
    USIDR = data;

    for (uint8_t i = 0; i < 8; i++) {
        asm volatile("nop");
    }

    PORTB &= ~(1 << i2c->config.scl_pin);

    for (uint16_t i = 0; i < i2c->config.timeout_us / 10; i++) {
        if (PINB & (1 << i2c->config.sda_pin)) {
            break;
        }
        _delay_us(10);
    }

    if (PINB & (1 << i2c->config.sda_pin)) {
        return I2C_ERR_NACK;
    }

    return I2C_OK;
}

i2c_status_t i2c_read_byte(i2c_t *i2c, uint8_t *data) {
    *data = 0xFF;

    for (uint8_t i = 0; i < 8; i++) {
        USIDR = 0x00;
        asm volatile("nop");
        if (i < 7) {
            *data |= USIBR;
        }
        asm volatile("nop");
    }

    return I2C_OK;
}

i2c_status_t i2c_address(i2c_t *i2c, uint8_t address, uint8_t read_write) {
    i2c_start(i2c);

    uint8_t addr_byte = (address << 1) | read_write;

    if (i2c_write_byte_wait_ack(i2c, addr_byte) != I2C_OK) {
        return I2C_ERR_BUS_ERROR;
    }

    return I2C_OK;
}

i2c_status_t i2c_read_reg(i2c_t *i2c, uint8_t address, uint8_t reg, uint8_t *data) {
    i2c_address(i2c, address, 0);

    if (i2c_write_byte_wait_ack(i2c, reg) != I2C_OK) {
        return I2C_ERR_BUS_ERROR;
    }

    return i2c_read_byte(i2c, data);
}

i2c_status_t i2c_write_reg(i2c_t *i2c, uint8_t address, uint8_t reg, uint8_t data) {
    i2c_address(i2c, address, 0);

    if (i2c_write_byte_wait_ack(i2c, reg) != I2C_OK) {
        return I2C_ERR_BUS_ERROR;
    }

    return i2c_write_byte_wait_ack(i2c, data);
}
