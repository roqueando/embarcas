#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "ssd1306/ssd1306.h"

#define SSD1306_CMD_MODE 0x00
#define SSD1306_DATA_MODE 0x40
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

static ssd1306_status_t ssd1306_write_cmd(ssd1306_t *display, uint8_t cmd) {
    i2c_status_t status;

    status = i2c_start(display->config.i2c);
    if (status != I2C_OK) return SSD1306_ERR_I2C;

    status = i2c_address(display->config.i2c, display->config.i2c_address, 0);
    if (status != I2C_OK) {
        i2c_stop(display->config.i2c);
        return SSD1306_ERR_I2C;
    }

    status = i2c_write_byte(display->config.i2c, SSD1306_CMD_MODE);
    if (status != I2C_OK) {
        i2c_stop(display->config.i2c);
        return SSD1306_ERR_I2C;
    }

    status = i2c_write_byte(display->config.i2c, cmd);
    i2c_stop(display->config.i2c);

    return (status == I2C_OK) ? SSD1306_OK : SSD1306_ERR_I2C;
}

static void ssd1306_set_position(ssd1306_t *display, uint8_t x, uint8_t y) {
    uint8_t page = y / 8;

    ssd1306_write_cmd(display, 0xB0 | page);
    ssd1306_write_cmd(display, x & 0x0F);
    ssd1306_write_cmd(display, 0x10 | (x >> 4));
}

ssd1306_status_t ssd1306_init(ssd1306_t *display, ssd1306_config_t config) {
    display->config = config;
    _delay_ms(10);

    ssd1306_write_cmd(display, 0xAE);
    ssd1306_write_cmd(display, 0xD5);
    ssd1306_write_cmd(display, 0x80);
    ssd1306_write_cmd(display, 0xA8);
    ssd1306_write_cmd(display, 0x3F);
    ssd1306_write_cmd(display, 0xD3);
    ssd1306_write_cmd(display, 0x00);
    ssd1306_write_cmd(display, 0x40);
    ssd1306_write_cmd(display, 0x8D);
    ssd1306_write_cmd(display, 0x14);
    ssd1306_write_cmd(display, 0x20);
    ssd1306_write_cmd(display, 0x00);
    ssd1306_write_cmd(display, 0xA1);
    ssd1306_write_cmd(display, 0xC8);
    ssd1306_write_cmd(display, 0xDA);
    ssd1306_write_cmd(display, 0x12);
    ssd1306_write_cmd(display, 0x81);
    ssd1306_write_cmd(display, 0xCF);
    ssd1306_write_cmd(display, 0xD9);
    ssd1306_write_cmd(display, 0xF1);
    ssd1306_write_cmd(display, 0xDB);
    ssd1306_write_cmd(display, 0x40);
    ssd1306_write_cmd(display, 0xA4);
    ssd1306_write_cmd(display, 0xA6);
    ssd1306_write_cmd(display, 0xAF);

    display->initialized = 1;
    return SSD1306_OK;
}

ssd1306_status_t ssd1306_clear(ssd1306_t *display) {
    i2c_status_t status;
    uint8_t page, col;

    for (page = 0; page < 8; page++) {
        ssd1306_set_position(display, 0, page * 8);

        status = i2c_start(display->config.i2c);
        if (status != I2C_OK) return SSD1306_ERR_I2C;
        status = i2c_address(display->config.i2c, display->config.i2c_address, 0);
        if (status != I2C_OK) {
            i2c_stop(display->config.i2c);
            return SSD1306_ERR_I2C;
        }
        status = i2c_write_byte(display->config.i2c, SSD1306_DATA_MODE);
        if (status != I2C_OK) {
            i2c_stop(display->config.i2c);
            return SSD1306_ERR_I2C;
        }

        for (col = 0; col < 128; col++) {
            i2c_write_byte(display->config.i2c, 0x00);
        }
        i2c_stop(display->config.i2c);
    }

    return SSD1306_OK;
}

ssd1306_status_t ssd1306_set_pixel(ssd1306_t *display, uint8_t x, uint8_t y) {
    i2c_status_t status;
    uint8_t page = y / 8;
    uint8_t bit = y % 8;

    ssd1306_set_position(display, x, y);

    status = i2c_start(display->config.i2c);
    if (status != I2C_OK) return SSD1306_ERR_I2C;
    status = i2c_address(display->config.i2c, display->config.i2c_address, 0);
    if (status != I2C_OK) {
        i2c_stop(display->config.i2c);
        return SSD1306_ERR_I2C;
    }
    status = i2c_write_byte(display->config.i2c, SSD1306_DATA_MODE);
    if (status != I2C_OK) {
        i2c_stop(display->config.i2c);
        return SSD1306_ERR_I2C;
    }
    i2c_write_byte(display->config.i2c, 1 << bit);
    i2c_stop(display->config.i2c);

    return (status == I2C_OK) ? SSD1306_OK : SSD1306_ERR_I2C;
}

ssd1306_status_t ssd1306_draw_box(ssd1306_t *display, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    uint8_t x, y;

    if (x0 >= SSD1306_WIDTH || y0 >= SSD1306_HEIGHT) {
        return SSD1306_ERR_INIT;
    }

    if (x1 >= SSD1306_WIDTH) x1 = SSD1306_WIDTH - 1;
    if (y1 >= SSD1306_HEIGHT) y1 = SSD1306_HEIGHT - 1;

    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++) {
            ssd1306_set_pixel(display, x, y);
        }
    }

    return SSD1306_OK;
}
