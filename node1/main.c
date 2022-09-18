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
	int data;
	while(1){
		data = read_adc(2);
		printf("\% i \r\n", data);
		}
}