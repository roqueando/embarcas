#pragma once

#include <stdint.h>

uint32_t timer(void);
void timer_start(uint8_t count_val);
uint8_t timer_read(void);
void timer_wait(void);
int timer_finished(void);
void timer_delay(uint8_t time);
void timer_init(void);
