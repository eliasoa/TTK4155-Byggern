#include <avr/io.h>
#include "uart.h"
#include "init.h"
#include <util/delay.h>

#define MYUBRR FOSC/16/BAUD-1


int main(void)
{
	xmem_init ();
	adc_timer();
	UART_Init();
	uint8_t data;
	while(1){
		uint8_t data = read_adc(1);
		
		struct data Multiboard_1.x_axis;
		printf("\% i \r\n", data);
		}
}