#include "attiny85.h"
#include "gpio/gpio.h"
#include "usi/i2c.h"
#include "ssd1306/ssd1306.h"
#include <util/delay.h>

#define SCL_PIN PB2
#define SDA_PIN PB0

static char nibble_to_hex(uint8_t nibble) {
    nibble &= 0x0F;
    return (nibble < 10) ? ('0' + nibble) : ('A' + nibble - 10);
}

int main(void) {
    uart_t uart = uart_init((uart_config_t){
        .tx_pin = PB3,
        .rx_pin = PB1,
        .baudrate = 9600
    });

    _delay_ms(500);

    uart_puts(&uart, "EMBARCAS INITIALIZING...\r\n");

    i2c_t i2c = i2c_init((i2c_config_t){
        .sda_pin = SDA_PIN,
        .scl_pin = SCL_PIN,
        .timeout_us = 10000
    });

    ssd1306_t display;
    ssd1306_status_t status;
    uint8_t retries;

    i2c = i2c_init((i2c_config_t){
        .sda_pin = PB0,
        .scl_pin = PB2,
        .timeout_us = 10000
    });

    _delay_ms(100);

    for (retries = 0; retries < 3; retries++) {
        status = ssd1306_init(&display, (ssd1306_config_t){
            .i2c_address = 0x3C,
            .i2c = &i2c
        });

        _delay_ms(10);

        if (status == SSD1306_OK) {
            uart_puts(&uart, "[SSD1306] OK\r\n");
            break;
        } else {
            uart_puts(&uart, "[...]");
        }
        _delay_ms(100);
    }


    if (status != SSD1306_OK) {
        i2c_status_t i2c_status;
        i2c_status = i2c_start(&i2c);
        _delay_ms(10);
        if (i2c_status == I2C_OK) {
            uint8_t test_data[] = {0xAE, 0xD5, 0x80, 0xA8, 0x3F};
            for (uint8_t i = 0; i < 5; i++) {
                i2c_write_byte(&i2c, test_data[i]);
                _delay_ms(1);
            }
            i2c_stop(&i2c);
        }
    }


    _delay_ms(2000);

    status = ssd1306_clear(&display);

    if (status != SSD1306_OK) {
        uart_puts(&uart, "[SSD1306] error on clear display\r\n");
    } else {
        uart_puts(&uart, "[SSD1306] display cleared\r\n");
    }
    _delay_ms(100);

    status = ssd1306_draw_box(&display, 10, 10, 117, 53);
    if (status != SSD1306_OK) {
        uart_puts(&uart, "[SSD1306] error on drawing box\r\n");
    } else {
        uart_puts(&uart, "[SSD1306] box drawn\r\n");
    }
    while (1) {
    }
}
