#ifndef _UART_DRIVER_H_
#define _UART_DRIVER_H_

void UART_Init( unsigned char ubrr );		// Initialization function

void UART_Transmit( unsigned char data );	// Transmit function

unsigned char UART_Receive( void ); // Recieve function

void UART_printf_link();  // Link printf to uart driver
#endif
