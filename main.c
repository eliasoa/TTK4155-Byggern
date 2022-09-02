/*
 * Byggern gruppe 36.c
 *
 * Created: 02.09.2022 10:00:44
 * Author : petteroj
 */ 

#include <avr/io.h>
//#include <util/delay.h>
//#include "UART_driver.h"


#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define morradi FOSC/16/BAUD-1

int data = 2;
unsigned char ch = 'harambe';

void main(void)
{
	while(1){
	UART_Init(morradi);
	UART_Transmit(ch);
}
}

void UART_Init( unsigned char ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	//return 0;
}

void UART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
	//return 0;
}


unsigned char UART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}
