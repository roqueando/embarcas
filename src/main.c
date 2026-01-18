#include "attiny85.h"
#include "gpio/gpio.h"
#include "usi/i2c.h"
#include "ssd1780/ssd1780.h"
#include <util/delay.h>

int main(void) {
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
}
