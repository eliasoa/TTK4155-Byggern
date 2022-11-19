#pragma once
#include "sam.h"

void adc_init( void );

uint16_t adc_read( void );

uint16_t ir_counter(uint16_t value);