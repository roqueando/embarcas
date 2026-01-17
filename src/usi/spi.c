/**
 * @file usi_spi.c
 * @brief USI SPI implementation for ATtiny85
 */

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "usi/spi.h"

static uint8_t usi_data = 0;

spi_t spi_init(spi_config_t config) {
    DDRB |= (1 << config.sclk_pin) | (1 << config.mosi_pin);
    DDRB &= ~(1 << config.miso_pin);

    USICR = (1 << USIWM0) | (1 << USICS1);

    switch (config.mode) {
        case SPI_MODE_0:
            USICR &= ~((1 << USIWM1) | (1 << USICS1));
            break;
        case SPI_MODE_1:
            USICR &= ~(1 << USIWM1);
            USICR |= (1 << USICS1);
            break;
        case SPI_MODE_2:
            USICR |= (1 << USIWM1) | (1 << USICS1);
            break;
        case SPI_MODE_3:
            USICR |= (1 << USIWM1);
            USICR &= ~(1 << USICS1);
            break;
    }

    PORTB &= ~((1 << config.mosi_pin) | (1 << config.miso_pin) | (1 << config.sclk_pin));

    spi_t spi = { .config = config };
    return spi;
}

uint8_t spi_transfer(spi_t *spi, uint8_t data) {
    USIDR = data;

    for (uint8_t i = 0; i < 8; i++) {
        asm volatile("nop");
    }

    return USIDR;
}

void spi_transfer_buf(spi_t *spi, const uint8_t *tx, uint8_t *rx, uint16_t len) {
    for (uint16_t i = 0; i < len; i++) {
        uint8_t data = tx[i];
        uint8_t recv = spi_transfer(spi, data);
        if (rx) {
            rx[i] = recv;
        }
    }
}

void spi_write(spi_t *spi, const uint8_t *data, uint16_t len) {
    for (uint16_t i = 0; i < len; i++) {
        spi_transfer(spi, data[i]);
    }
}
