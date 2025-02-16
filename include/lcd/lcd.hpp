#pragma once

#define D0 {pin_mode::OUTPUT, 0, available_port::B}
#define D1 {pin_mode::OUTPUT, 1, available_port::B}
#define D2 {pin_mode::OUTPUT, 2, available_port::B}
#define D3 {pin_mode::OUTPUT, 3, available_port::B}
#define D4 {pin_mode::OUTPUT, 4, available_port::B}
#define D5 {pin_mode::OUTPUT, 5, available_port::B}
#define D6 {pin_mode::OUTPUT, 6, available_port::B}
#define D7 {pin_mode::OUTPUT, 7, available_port::B}

#define LCD_RS_PIN {pin_mode::OUTPUT, 0, available_port::C}
//#define RW {pin_mode::OUTPUT, 1, available_port::C}
#define LCD_EN_PIN {pin_mode::OUTPUT, 2, available_port::C}


void lcd_init();
void lcd_char(char value);
