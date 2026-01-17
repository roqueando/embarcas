/**
 * @file uart.c
 * @brief UART bit-banging implementation for ATtiny85
 */

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart/uart.h"

static uart_t uart;

uart_t uart_init(uart_config_t config) {
    DDRB |= (1 << config.tx_pin);
    DDRB &= ~(1 << config.rx_pin);
    PORTB &= ~(1 << config.rx_pin);

    uart.config = config;
    return uart;
}

void uart_putc(uart_t *uart, uint8_t data) {
    for (uint8_t i = 0; i < 8; i++) {
        if (data & (1 << i)) {
            PORTB |= (1 << uart->config.tx_pin);
        } else {
            PORTB &= ~(1 << uart->config.tx_pin);
        }
    }
}

void uart_puts(uart_t *uart, const char *str) {
    while (*str) {
        uart_putc(uart, (uint8_t)*str);
        str++;
    }
}

uint8_t uart_getc(uart_t *uart, uint8_t *data, uint32_t timeout_us) {
    uint32_t half_bit = (uart->config.baudrate / 2);
    uint32_t start;

    PORTB &= ~(1 << uart->config.rx_pin);

    for (start = 0; start < timeout_us; start++) {
        if (PINB & (1 << uart->config.rx_pin)) {
            *data = (PINB >> uart->config.rx_pin) & 1;
            return 1;
        }
    }

    return 0;
}

uint8_t uart_available(uart_t *uart) {
    return PINB & (1 << uart->config.rx_pin);
}
