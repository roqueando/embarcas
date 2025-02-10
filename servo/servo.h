#ifndef SERVO_H
#define SERVO_H
#include "../io/io.h"

// BUTTONS
#define CLOCKWISE_BUTTON {mode::INPUT, 0, available_port::D}
#define COUNTER_CLOCKWISE_BUTTON {mode::INPUT, 1, available_port::D}

// LEDs
#define CLOCKWISE_LED {mode::OUTPUT, 0, available_port::C}
#define COUNTER_CLOCKWISE_LED {mode::OUTPUT, 1, available_port::C}

// MOTOR
#define MOTOR {mode::OUTPUT, 2, available_port::D}

static int MOTOR_HALF_RIGHT = 2000;
static int MOTOR_HALF_LEFT = 100;

void servo_init();
void turn_clockwise();
void turn_counter_clockwise();

#endif // SERVO_H
