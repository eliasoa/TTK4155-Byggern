#ifndef UART_H_
#define UART_H_

void UART_Init( unsigned char ubrr );

void UART_Transmit( unsigned char data );

unsigned char UART_Receive();

void UART_printf_link();

#endif