#ifndef HAL_SSD1306_H
#define HAL_SSD1306_H

#include <stdint.h>
#include "usi/i2c.h"

typedef enum {
    SSD1306_OK,
    SSD1306_ERR_I2C,
    SSD1306_ERR_INIT,
} ssd1306_status_t;

typedef struct {
    uint8_t i2c_address;
    i2c_t *i2c;
    uint8_t rst_pin;
} ssd1306_config_t;

typedef struct {
    ssd1306_config_t config;
    uint8_t initialized;
} ssd1306_t;

ssd1306_status_t ssd1306_init(ssd1306_t *display, ssd1306_config_t config);
ssd1306_status_t ssd1306_clear(ssd1306_t *display);
ssd1306_status_t ssd1306_draw_box(ssd1306_t *display, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
ssd1306_status_t ssd1306_set_pixel(ssd1306_t *display, uint8_t x, uint8_t y);

#endif
