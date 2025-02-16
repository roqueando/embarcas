#pragma once

#include <io/io.hpp>

// BUTTONS
#define CLOCKWISE_BUTTON {pin_mode::INPUT, 0, available_port::B}
#define COUNTER_CLOCKWISE_BUTTON {pin_mode::INPUT, 7, available_port::D}

// LEDs
#define CLOCKWISE_LED {pin_mode::OUTPUT, 0, available_port::C}
#define COUNTER_CLOCKWISE_LED {pin_mode::OUTPUT, 1, available_port::C}
#define DEBUG_LED {pin_mode::OUTPUT, 4, available_port::D}

// MOTOR
#define MOTOR {pin_mode::OUTPUT, 3, available_port::D}

static int MOTOR_HALF_RIGHT = 1000;
static int MOTOR_HALF_LEFT = 100;

void servo_init();
void turn_clockwise();
void turn_counter_clockwise();
void motor_on(int side);

