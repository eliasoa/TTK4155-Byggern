#ifndef _UART_DRIVER_H_
#define _UART_DRIVER_H_

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>


void UART_Init( unsigned char ubrr );		// Initialization function

void UART_Transmit( unsigned char data );	// Transmit function

unsigned char UART_Receive( void );

void UART_printf_link();
#endif