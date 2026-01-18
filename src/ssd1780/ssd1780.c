#include "ssd1780/ssd1780.h"
#include <avr/io.h>
#include <util/delay.h>

#define SSD1780_CMD_MODE 0x00
#define SSD1780_DATA_MODE 0x40

static ssd1780_status_t ssd1780_send_command(ssd1780_t *display, uint8_t cmd);
static ssd1780_status_t ssd1780_send_data(ssd1780_t *display, uint8_t data);
static ssd1780_status_t ssd1780_set_address(ssd1780_t *display,
                                                uint8_t x0, uint8_t y0,
                                                uint8_t x1, uint8_t y1);

static ssd1780_status_t ssd1780_send_command(ssd1780_t *display, uint8_t cmd) {
    i2c_status_t status;

    status = i2c_start(display->config.i2c);
    if (status != I2C_OK) return SSD1780_ERR_I2C;

    status = i2c_address(display->config.i2c, display->config.i2c_address, 0);
    if (status != I2C_OK) {
        i2c_stop(display->config.i2c);
        return SSD1780_ERR_I2C;
    }

    status = i2c_write_byte(display->config.i2c, SSD1780_CMD_MODE);
    if (status != I2C_OK) {
        i2c_stop(display->config.i2c);
        return SSD1780_ERR_I2C;
    }

    status = i2c_write_byte(display->config.i2c, cmd);
    i2c_stop(display->config.i2c);

    return (status == I2C_OK) ? SSD1780_OK : SSD1780_ERR_I2C;
}

static ssd1780_status_t ssd1780_send_data(ssd1780_t *display, uint8_t data) {
    i2c_status_t status;

    status = i2c_start(display->config.i2c);
    if (status != I2C_OK) return SSD1780_ERR_I2C;

    status = i2c_address(display->config.i2c, display->config.i2c_address, 0);
    if (status != I2C_OK) {
        i2c_stop(display->config.i2c);
        return SSD1780_ERR_I2C;
    }

    status = i2c_write_byte(display->config.i2c, SSD1780_DATA_MODE);
    if (status != I2C_OK) {
        i2c_stop(display->config.i2c);
        return SSD1780_ERR_I2C;
    }

    status = i2c_write_byte(display->config.i2c, data);
    i2c_stop(display->config.i2c);

    return (status == I2C_OK) ? SSD1780_OK : SSD1780_ERR_I2C;
}

static ssd1780_status_t ssd1780_set_address(ssd1780_t *display,
                                                uint8_t x0, uint8_t y0,
                                                uint8_t x1, uint8_t y1) {
    ssd1780_status_t status;

    status = ssd1780_send_command(display, 0x2A);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_data(display, x0);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_data(display, x1);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0x2B);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_data(display, y0);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_data(display, y1);
    if (status != SSD1780_OK) return status;

    return ssd1780_send_command(display, 0x2C);
}

ssd1780_status_t ssd1780_init(ssd1780_t *display, ssd1780_config_t config) {
    ssd1780_status_t status;
    uint8_t i;

    display->config = config;
    display->initialized = 0;

    _delay_ms(10);

    status = ssd1780_send_command(display, 0xAE);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0x81);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_data(display, 0x7F);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0xA8);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_data(display, config.height - 1);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0xD3);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_data(display, 0x00);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0x40);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0xA1);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0xC8);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0xDA);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_data(display, 0x12);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0xD5);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_data(display, 0x80);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0xD9);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_data(display, 0xF1);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0xDB);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_data(display, 0x40);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0x20);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_data(display, 0x00);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0xA4);
    if (status != SSD1780_OK) return status;

    status = ssd1780_send_command(display, 0xA6);
    if (status != SSD1780_OK) return status;

    status = ssd1780_clear(display, SSD1780_COLOR_BLACK);
    if (status != SSD1780_OK) return status;

    display->initialized = 1;

    return ssd1780_display_on(display);
}

ssd1780_status_t ssd1780_clear(ssd1780_t *display, ssd1780_color_t color) {
    uint16_t total_pixels;
    ssd1780_status_t status;
    uint16_t i;

    total_pixels = (uint16_t)display->config.width * (uint16_t)display->config.height;

    status = ssd1780_set_address(display, 0, 0,
                                display->config.width - 1,
                                display->config.height - 1);
    if (status != SSD1780_OK) return status;

    for (i = 0; i < total_pixels; i++) {
        status = ssd1780_send_data(display, color);
        if (status != SSD1780_OK) return status;
    }

    return SSD1780_OK;
}

ssd1780_status_t ssd1780_draw_box(ssd1780_t *display,
                                uint8_t x0, uint8_t y0,
                                uint8_t x1, uint8_t y1,
                                ssd1780_color_t color) {
    ssd1780_status_t status;
    uint8_t x, y;
    uint16_t width, height;

    if (x0 >= display->config.width || y0 >= display->config.height) {
        return SSD1780_ERR_INVALID_PARAM;
    }

    if (x1 >= display->config.width) x1 = display->config.width - 1;
    if (y1 >= display->config.height) y1 = display->config.height - 1;

    if (x0 > x1) {
        uint8_t temp = x0;
        x0 = x1;
        x1 = temp;
    }

    if (y0 > y1) {
        uint8_t temp = y0;
        y0 = y1;
        y1 = temp;
    }

    status = ssd1780_set_address(display, x0, y0, x1, y1);
    if (status != SSD1780_OK) return status;

    width = (uint16_t)(x1 - x0 + 1);
    height = (uint16_t)(y1 - y0 + 1);

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            status = ssd1780_send_data(display, color);
            if (status != SSD1780_OK) return status;
        }
    }

    return SSD1780_OK;
}

ssd1780_status_t ssd1780_display_on(ssd1780_t *display) {
    return ssd1780_send_command(display, 0xAF);
}

ssd1780_status_t ssd1780_display_off(ssd1780_t *display) {
    return ssd1780_send_command(display, 0xAE);
}
