/**
 * @file uart.h
 * @brief UART bit-banging for ATtiny85
 *
 * ATtiny85 has no hardware UART, so we implement
 * software (bit-banging) UART for basic communication.
 */

#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdint.h>

/**
 * @defgroup hal_uart UART
 * @brief Software UART (bit-banging)
 * @{
 */

/**
 * @brief UART configuration
 */
typedef struct {
    uint8_t tx_pin;
    uint8_t rx_pin;
    uint32_t baudrate;
} uart_config_t;

/**
 * @brief UART handle
 */
typedef struct {
    uart_config_t config;
} uart_t;

/**
 * @brief Initialize UART
 *
 * Configures TX/RX pins and baudrate.
 *
 * @param config UART configuration (TX/RX pins, baudrate)
 * @return UART handle
 */
uart_t uart_init(uart_config_t config);

/**
 * @brief Transmit byte
 *
 * Sends single byte via TX pin.
 *
 * @param uart UART handle
 * @param data Byte to transmit
 */
void uart_putc(uart_t *uart, uint8_t data);

/**
 * @brief Transmit string
 *
 * Sends null-terminated string via TX pin.
 *
 * @param uart UART handle
 * @param str Null-terminated string
 */
void uart_puts(uart_t *uart, const char *str);

/**
 * @brief Receive byte with timeout
 *
 * Waits for start bit, then receives byte via RX pin.
 *
 * @param uart UART handle
 * @param data Pointer to store received byte
 * @param timeout_us Timeout in microseconds
 * @return Non-zero if byte received
 */
uint8_t uart_getc(uart_t *uart, uint8_t *data, uint32_t timeout_us);

/**
 * @brief Check if data available
 *
 * @param uart UART handle
 * @return Non-zero if start bit detected
 */
uint8_t uart_available(uart_t *uart);

/** @} */ // end of hal_uart

#endif // HAL_UART_H
