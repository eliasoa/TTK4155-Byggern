#pragma once


void pwm_init( void );

void servo_get_pos(uint8_t pos);

int map(int x, int in_min, int in_max, int out_min, int out_max);