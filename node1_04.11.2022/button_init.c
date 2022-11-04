#include <avr/io.h>

void button_init( void ){
	SFIOR &= ~(1 << PUD);
	DDRB &= ~(1<<PB2); // PIN B2 as input
	PORTB |= (1<<PB2); // Enable internal pull up on PB2
}