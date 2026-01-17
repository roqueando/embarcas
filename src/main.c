#include "attiny85.h"
#include <util/delay.h>

int main(void) {
    uart_t uart = uart_init((uart_config_t){
        .tx_pin = PB0,
        .rx_pin = PB1,
        .baudrate = 9600
    });

    _delay_ms(2000);

    while (1) {
        uart_puts(&uart, "Hello");
        _delay_ms(5);
    }
}
