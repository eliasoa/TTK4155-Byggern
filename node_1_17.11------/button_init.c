#include <avr/io.h>

// To read a button state PINB & (1<<PBx)

void button_init( void ){
	SFIOR &= ~(1 << PUD);
	DDRB &= ~(1<<PB2)|(1<<PB1)|(1<<PB0); // PIN B0 B1 B2 as input
	PORTB |= (1<<PB2)|(1<<PB1)|(1<<PB0); // Enable internal pull up on PB2
}