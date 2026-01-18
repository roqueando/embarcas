#include "attiny85.h"
#include "gpio/gpio.h"
//#include "usi/i2c.h"
//#include "ssd1306/ssd1306.h"
#include <util/delay.h>

#define SCL_PIN PB2
#define SDA_PIN PB0
#define DBG_LED GPIO_PB3

static char nibble_to_hex(uint8_t nibble) {
    nibble &= 0x0F;
    return (nibble < 10) ? ('0' + nibble) : ('A' + nibble - 10);
}

void gpio_pcint_cb(gpio_pin_t pin) {
  if(gpio_is_high(pin)) {
    gpio_write(DBG_LED, GPIO_HIGH);
  } else {
    gpio_write(DBG_LED, GPIO_LOW);
  }
}

void init_input_sensor() {
  gpio_pin_t input_sensor_port = GPIO_PB1;
  gpio_mode_t input_sensor_mode = GPIO_MODE_INPUT;
  gpio_pcint_mode_t input_sensor_interrupt = GPIO_PCINT_ANY;

  gpio_init(input_sensor_port, input_sensor_mode);
  gpio_set_input(input_sensor_port);
  //gpio_set_input_pullup(input_sensor_port);
  gpio_enable_pcint(input_sensor_port, gpio_pcint_cb);
}

int main(void) {
  sei();
  gpio_pin_t dbg_led = GPIO_PB3;
  gpio_mode_t dbg_led_mode = GPIO_MODE_OUTPUT;

  gpio_init(dbg_led, dbg_led_mode);
  gpio_set_output(dbg_led);

  init_input_sensor();

  /*
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
            .i2c = &i2c,
            .rst_pin = 0xFF
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

    while (1) {
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
        _delay_ms(100);
    }
  */
}
