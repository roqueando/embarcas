#include <io/io.hpp>
#include <rgb/rgb.hpp>

port get_port(uint8_t pin)
{
    return {pin_mode::OUTPUT, pin, available_port::D};
}

void rgb_color(int led)
{
    port led_r_pin = get_port(LED_R_PIN);
    port led_g_pin = get_port(LED_G_PIN);
    port led_b_pin = get_port(LED_B_PIN);

    if (led & RED)
    {
        digital_write(led_r_pin, pin_state::HIGH);
    }
    else
    {
        digital_write(led_r_pin, pin_state::LOW);
    }

    if (led & BLUE)
    {
        digital_write(led_g_pin, pin_state::HIGH);
    }
    else
    {
        digital_write(led_g_pin, pin_state::LOW);
    }

    if (led & GREEN)
    {
        digital_write(led_b_pin, pin_state::HIGH);
    }
    else
    {
        digital_write(led_b_pin, pin_state::LOW);
    }
}

void turn_on(int led)
{
    if (led & RED)
        digital_write(get_port(LED_R_PIN), pin_state::HIGH);
    if (led & BLUE)
        digital_write(get_port(LED_B_PIN), pin_state::HIGH);
    if (led & GREEN)
        digital_write(get_port(LED_G_PIN), pin_state::HIGH);
}

void turn_off(int led)
{
    if (led & RED)
        digital_write(get_port(LED_R_PIN), pin_state::LOW);
    if (led & BLUE)
        digital_write(get_port(LED_B_PIN), pin_state::LOW);
    if (led & GREEN)
        digital_write(get_port(LED_G_PIN), pin_state::LOW);
}

void rgb_init()
{
    port led_r_pin = {pin_mode::OUTPUT, LED_R_PIN, available_port::D};
    port led_g_pin = {pin_mode::OUTPUT, LED_G_PIN, available_port::D};
    port led_b_pin = {pin_mode::OUTPUT, LED_B_PIN, available_port::D};

    set_port_direction(led_r_pin);
    set_port_direction(led_g_pin);
    set_port_direction(led_b_pin);
}

