#include "attiny85.h"
#include "gpio/gpio.h"
#include "usi/i2c.h"
#include "ssd1780/ssd1780.h"
#include <util/delay.h>

#define SCL_PIN PB2
#define SDA_PIN PB0

int main(void) {
    uart_t uart = uart_init((uart_config_t){
        .tx_pin = PB3,
        .rx_pin = PB1,
        .baudrate = 9600
    });

    i2c_t i2c = i2c_init((i2c_config_t){
        .sda_pin = SDA_PIN,
        .scl_pin = SCL_PIN,
        .timeout_us = 10000
    });

    uart_puts(&uart, "I2C Scanner:\r\n");
    uint8_t data;


    for (uint8_t addr = 0x00; addr < 0x80; addr++) {
        i2c_address(&i2c, addr, 0);

        if (i2c_write_byte_wait_ack(&i2c, addr) == I2C_OK) {
            uint8_t found = 1;
            uart_puts(&uart, "Device found at: 0x");
            uart_putc(&uart, (addr >> 4) | 0x0F);
            uart_puts(&uart, "\r\n");

            for (uint8_t reg = 0; reg < 0x10; reg++) {
                if (i2c_read_reg(&i2c, addr, reg, &data) != I2C_OK) {
                    uart_puts(&uart, "  R");
                    uart_putc(&uart, reg);
                    found = 1;
                }
            }

            if (found) {
                uart_puts(&uart, "\r\n");
            }
        } else {
            uart_puts(&uart, ".");
        }

        _delay_ms(10);
    }

    uart_puts(&uart, "\r\nScan complete.\r\n");

    while (1) {
    }
    /*
    i2c_t i2c;
    ssd1780_t display;
    ssd1780_status_t status;
    uint8_t retries;

    i2c = i2c_init((i2c_config_t){
        .sda_pin = PB0,
        .scl_pin = PB2,
        .timeout_us = 10000
    });

    _delay_ms(100);

    for (retries = 0; retries < 3; retries++) {

        status = ssd1780_init(&display, (ssd1780_config_t){
            .width = 128,
            .height = 64,
            .i2c_address = 0x3C,
            .i2c = &i2c
        });

        _delay_ms(10);

        if (status == SSD1780_OK) {
            break;
        }
        _delay_ms(100);
    }


    if (status != SSD1780_OK) {
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
    while (1) {
        _delay_ms(100);

        status = ssd1780_display_on(&display);

        _delay_ms(200);

        status = ssd1780_clear(&display, SSD1780_COLOR_BLACK);
        _delay_ms(100);

        status = ssd1780_draw_box(&display, 10, 10, 117, 53, SSD1780_COLOR_WHITE);
    }
    */
}
