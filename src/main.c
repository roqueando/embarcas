#include "attiny85.h"
#include "gpio/gpio.h"
#include "usi/i2c.h"
#include "ssd1306/ssd1306.h"
#include <util/delay.h>

#define SCL_PIN PB2
#define SDA_PIN PB0
#define UART_TX PB3
#define UART_RX PB1

static char nibble_to_hex(uint8_t nibble) {
    nibble &= 0x0F;
    return (nibble < 10) ? ('0' + nibble) : ('A' + nibble - 10);
}

int main(void) {
    uart_t uart = uart_init((uart_config_t){
        .tx_pin = UART_TX,
        .rx_pin = UART_RX,
        .baudrate = 9600
    });

    _delay_ms(500);

    uart_puts(&uart, "SSD1306 Test\r\n");

    i2c_t i2c = i2c_init((i2c_config_t){
        .sda_pin = SDA_PIN,
        .scl_pin = SCL_PIN,
        .timeout_us = 10000
    });

    ssd1306_t display;

    uart_puts(&uart, "Init display...\r\n");
    ssd1306_status_t status = ssd1306_init(&display, (ssd1306_config_t){
        .i2c_address = 0x3C,
        .i2c = &i2c
    });

    if (status == SSD1306_OK) {
        uart_puts(&uart, "Display OK!\r\n");
        _delay_ms(100);

        uart_puts(&uart, "Drawing box...\r\n");
        ssd1306_draw_box(&display, 10, 10, 50, 50);
        uart_puts(&uart, "Done.\r\n");
    } else {
        uart_puts(&uart, "Display FAIL\r\n");
    }

    while (1) {
    }
}
