#include <avr/io.h>
#include "uart.h"
#include <stdio.h>


void UART_Init( void )
{
	/* Set baud rate */
	int ubrr = 31;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	//return 0;
	/* Link printtf to */
	UART_printf_link();
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


unsigned char UART_Receive()
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}

void UART_printf_link()
{
	fdevopen((int (*)(char, FILE*))UART_Transmit, (int (*)(FILE*))UART_Receive);
}