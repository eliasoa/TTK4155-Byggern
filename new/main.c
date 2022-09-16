#include <avr/io.h>
#include "uart.h"
#include "init.h"
#include <util/delay.h>

#define MYUBRR FOSC/16/BAUD-1


int main(void)
{
xmem_init ();
UART_Init(MYUBRR);

	
while(1){
	
}		
}
