#pragma once
#include <avr/io.h>


void oled_init( void ); // Init OLED, from data sheet

void oled_print( char c );

void oled_write_command( uint8_t data );

void oled_write_data( uint8_t data );	// Write data -> 

void oled_clear( void );	// Clears screen

void oled_fill ( void ); // Fills the OLED screen, fucks with RAM

void oled_pos(uint8_t row, uint8_t column); // Set "pointer" to row and column

void oled_goto_line ( uint8_t row );

void oled_goto_column ( uint8_t column );

void oled_print_arrow ( uint8_t row , uint8_t col );

void oled_printf ( char* string );

void oled_reset ( void );