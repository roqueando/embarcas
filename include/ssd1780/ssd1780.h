/**
 * @file ssd1780.h
 * @brief SSD1780 LCD Display Driver
 *
 * SSD1780 is a CSTN LCD driver controller from Solomon Systech.
 * Supports up to 104x80 resolution with 4K color and graphics acceleration.
 */

#ifndef HAL_SSD1780_H
#define HAL_SSD1780_H

#include <stdint.h>
#include "usi/i2c.h"

/**
 * @defgroup hal_ssd1780 SSD1780 LCD Display Driver
 * @brief Driver for SSD1780 CSTN LCD controller
 * @{
 */

/**
 * @brief SSD1780 display status
 */
typedef enum {
    SSD1780_OK,                    ///< Success
    SSD1780_ERR_I2C,              ///< I2C communication error
    SSD1780_ERR_INIT,             ///< Initialization failed
    SSD1780_ERR_INVALID_PARAM,     ///< Invalid parameter
} ssd1780_status_t;

/**
 * @brief Display configuration
 */
typedef struct {
    uint8_t width;                ///< Display width in pixels
    uint8_t height;               ///< Display height in pixels
    uint8_t i2c_address;         ///< I2C slave address (7-bit)
    i2c_t *i2c;                 ///< Pointer to I2C handle
} ssd1780_config_t;

/**
 * @brief SSD1780 display handle
 */
typedef struct {
    ssd1780_config_t config;
    uint8_t initialized;
} ssd1780_t;

/**
 * @brief Color definitions (8-bit color)
 *
 * SSD1780 uses 8-bit color format (RGB 332)
 */
typedef enum {
    SSD1780_COLOR_BLACK = 0x00,   ///< Black (00000000)
    SSD1780_COLOR_RED   = 0xE0,   ///< Red   (11100000)
    SSD1780_COLOR_GREEN = 0x1C,   ///< Green (00011100)
    SSD1780_COLOR_BLUE  = 0x03,   ///< Blue  (00000011)
    SSD1780_COLOR_WHITE = 0xFF,   ///< White (11111111)
    SSD1780_COLOR_YELLOW = 0xFC,   ///< Yellow (11111100)
    SSD1780_COLOR_CYAN  = 0x1F,   ///< Cyan   (00011111)
    SSD1780_COLOR_MAGENTA = 0xE3,  ///< Magenta (11100011)
} ssd1780_color_t;

/**
 * @brief Initialize SSD1780 display
 *
 * @param display Pointer to display handle
 * @param config Display configuration
 * @return SSD1780 status
 */
ssd1780_status_t ssd1780_init(ssd1780_t *display, ssd1780_config_t config);

/**
 * @brief Clear display with specified color
 *
 * @param display Pointer to display handle
 * @param color Fill color
 * @return SSD1780 status
 */
ssd1780_status_t ssd1780_clear(ssd1780_t *display, ssd1780_color_t color);

/**
 * @brief Draw a filled rectangle (box)
 *
 * @param display Pointer to display handle
 * @param x0 Start X coordinate (0-indexed)
 * @param y0 Start Y coordinate (0-indexed)
 * @param x1 End X coordinate (inclusive)
 * @param y1 End Y coordinate (inclusive)
 * @param color Fill color
 * @return SSD1780 status
 */
ssd1780_status_t ssd1780_draw_box(ssd1780_t *display,
                                uint8_t x0, uint8_t y0,
                                uint8_t x1, uint8_t y1,
                                ssd1780_color_t color);

/**
 * @brief Turn display on
 *
 * @param display Pointer to display handle
 * @return SSD1780 status
 */
ssd1780_status_t ssd1780_display_on(ssd1780_t *display);

/**
 * @brief Turn display off
 *
 * @param display Pointer to display handle
 * @return SSD1780 status
 */
ssd1780_status_t ssd1780_display_off(ssd1780_t *display);

/** @} */ // end of hal_ssd1780

#endif // HAL_SSD1780_H
