#include "servo.h"
#include <util/delay.h>

void motor_on(int side)
{
    digital_write(MOTOR, pin_state::HIGH);
    for(int i = 0; i < side; i++);
    digital_write(MOTOR, pin_state::LOW);
}

void servo_init()
{
    set_port_direction(CLOCKWISE_BUTTON);
    set_port_direction(COUNTER_CLOCKWISE_BUTTON);
    set_port_direction(CLOCKWISE_LED);
    set_port_direction(COUNTER_CLOCKWISE_LED);
    set_port_direction(MOTOR);
}

void turn_clockwise()
{
    int clockwise_button = digital_read(CLOCKWISE_BUTTON);
    if (clockwise_button) {
        digital_write(CLOCKWISE_LED, pin_state::HIGH);
        motor_on(MOTOR_HALF_RIGHT);
    } else {
        digital_write(CLOCKWISE_LED, pin_state::LOW);
    }
}

void turn_counter_clockwise()
{
    int counter_clockwise_button = digital_read(COUNTER_CLOCKWISE_BUTTON);
    if (counter_clockwise_button) {
        digital_write(COUNTER_CLOCKWISE_LED, pin_state::HIGH);
        motor_on(MOTOR_HALF_LEFT);
    } else {
        digital_write(COUNTER_CLOCKWISE_LED, pin_state::LOW);
    }

}

