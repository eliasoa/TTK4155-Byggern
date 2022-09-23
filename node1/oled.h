#pragma once
#include <avr/io.h>

void oled_init( void );
void oled_print( void );

void oled_write_command( uint8_t data );

void oled_write_data( uint8_t data );

void oled_clear( void );

void oled_fill ( void );