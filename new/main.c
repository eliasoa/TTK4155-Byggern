#include <avr/io.h>
#include "uart.h"
#include "init.h"
#include <util/delay.h>

#define MYUBRR FOSC/16/BAUD-1


int main(void)
{
xmem_init ();
UART_Init(MYUBRR);
		
}




//xmem_write(0,0x00); // Write to OLED
//_delay_ms(5000);
//xmem_write ( 1, 0x400); // Write to ADC ADDRESS
//_delay_ms(5000);
//xmem_write ( 1, 0X800); // Write to SRAM ADDRESS
//_delay_ms(5000);