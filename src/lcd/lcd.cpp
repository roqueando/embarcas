#include <lcd/lcd.hpp>
#include <io/io.hpp>

void lcd_init()
{
    set_port_direction(LCD_RS_PIN);
    set_port_direction(LCD_EN_PIN);
    delay_mili(15);

    set_port_direction(D0);
    set_port_direction(D1);
    set_port_direction(D2);
    set_port_direction(D3);
    set_port_direction(D4);
    set_port_direction(D5);
    set_port_direction(D6);
    set_port_direction(D7);

}

void lcd_char(char value)
{
    char hi_nibble = (value >> 4) & 0x0F;
    char low_nibble = (value >> 2) & 0x0F;

    digital_write(LCD_RS_PIN, pin_state::HIGH);

    delay_micro(40);
}
