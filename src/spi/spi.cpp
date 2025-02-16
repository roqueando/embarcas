#include <spi/spi.hpp>
#include <io/io.hpp>

void send_to_lcd(uint8_t data, bool is_command)
{
    digital_write(RS_PIN, !is_command ? pin_state::HIGH : pin_state::LOW);

    // 4 high bits
    digital_write(LATCH_PIN, pin_state::LOW);
    shift_out_bitbang(data >> 4);
    digital_write(LATCH_PIN, pin_state::HIGH);
    digital_write(EN_PIN, pin_state::HIGH);
    delay_mili(15);
    digital_write(EN_PIN, pin_state::LOW);

    // 4 low bits
    digital_write(LATCH_PIN, pin_state::LOW);
    shift_out_bitbang(data & 0x0F);
    digital_write(LATCH_PIN, pin_state::HIGH);
    digital_write(EN_PIN, pin_state::HIGH);
    delay_mili(15);
    digital_write(EN_PIN, pin_state::LOW);
}

void shift_out_init()
{
    set_port_direction(MOSI_PIN);
    set_port_direction(SCK_PIN);
    set_port_direction(LATCH_PIN);
    set_port_direction(EN_PIN);
    set_port_direction(RS_PIN);

    send_to_lcd(0x28, true);
}
void shift_out_bitbang(uint8_t data)
{
    for (int i = 0; i < 7; i++)
    {
        if ((data >> 1) & 1) {
            digital_write(MOSI_PIN, pin_state::HIGH);
        } else {
            digital_write(MOSI_PIN, pin_state::LOW);
        }

        digital_write(SCK_PIN, pin_state::HIGH);
        delay_micro(40);
        digital_write(SCK_PIN, pin_state::LOW);
    }
}
