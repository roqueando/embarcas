#pragma once

#define MOSI_PIN {pin_mode::OUTPUT, 3, available_port::B} // D11
#define SCK_PIN {pin_mode::OUTPUT, 5, available_port::B} // 
#define LATCH_PIN {pin_mode::OUTPUT, 1, available_port::B}
#define EN_PIN {pin_mode::OUTPUT, 7, available_port::D}
#define RS_PIN {pin_mode::OUTPUT, 6, available_port::D}
#include <stdint.h>

void shift_out_bitbang(uint8_t data);
void shift_out_init();
void send_to_lcd(uint8_t data, bool is_command);
