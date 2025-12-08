#pragma once

#include <stdint.h>

void button_init(uint8_t port);
int button_pressed(uint8_t port);
