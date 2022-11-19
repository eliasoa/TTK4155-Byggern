#pragma once
#include <avr/io.h>

// Init OLED, from data sheet
void oled_init( void ); 
// Print
void oled_print( char c );
// Write command data
void oled_write_command( uint8_t data );
// Write data -> 
void oled_write_data( uint8_t data );	
// Clears screen
void oled_clear( void );	
// Fills the OLED screen, fucks with RAM
void oled_fill ( void ); 
// Set "pointer" to row and column
void oled_pos(uint8_t row, uint8_t column);
// Goes to row
void oled_goto_line ( uint8_t row );	
// Goes to column
void oled_goto_column ( uint8_t column );	
// Prints arrow
void oled_print_arrow ( uint8_t row , uint8_t col );	
// Prints string to screen
void oled_printf ( char* string );	
// Resets oled
void oled_reset ( void );	