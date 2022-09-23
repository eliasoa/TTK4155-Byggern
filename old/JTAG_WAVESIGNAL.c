/*
 * GccApplication1.c
 *
 * Created: 02.09.2022 13:30:12
 * Author : petteroj
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 4915200
#define FOSC 4915200

int main(void)
{
	
	DDRA = 0b11111111;
    while (1) 
    {
	_delay_ms(5000);
	PORTA |= (1 << 0);
	_delay_ms(5000);
	PORTA = 0;
    }
return(0);
}

