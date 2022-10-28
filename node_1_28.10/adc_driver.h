#pragma once
#include <avr/io.h>

typedef enum {
	LEFT=0,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL
} Joystick_position ;

void adc_timer(); // Clock signal for ADC timer, inherited from the ATmega162 

uint8_t read_adc ( uint8_t channel); // Read channel x from ADC

uint8_t joystick_analog_position_percentage (uint8_t analog_value, uint8_t channel); // Convert from 0-255 to -100% to 100%

long map(long x, long in_min, long in_max, long out_min, long out_max); // Mapping function from https://www.arduino.cc/reference/en/language/functions/math/map/

Joystick_position Joystick_direction ( uint8_t analog_value, uint8_t channel) ; // Function that returns the joystick direction (LEFT, RIGT, UP, DOWN, NEAUTRAL). input is analog value and channel