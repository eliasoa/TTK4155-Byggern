#include <avr/io.h>
#include "uart.h"
#include "adc_driver.h"
#include "xmem.h"
#include "oled.h"
#include "oled_menu.h"
#include "button_init.h"
#include "spi_driver.h"
#include "mcp2512.h"
#include "can_driver.h"

#define F_CPU 4915200 // Clock Speed

#include <util/delay.h>
#include <stdio.h>
#include "oled.h"
#include <avr/interrupt.h>

#define BAUD 9600 // Baud rate


volatile uint8_t* adc = (uint8_t*)0x1400;
volatile uint8_t* oled_command = (uint8_t*)0x1000;
volatile uint8_t* oled_data = (uint8_t*)0x1200;


int main(void)
{
	xmem_init ();
	button_init();
	adc_timer();
	UART_Init();
	oled_init();
	oled_clear();
	_delay_ms(1000);
	uint8_t row = 0;
	uint8_t column = 0;
	oled_pos(row,column);
		
	can_init();
	

	message test_struct;
	test_struct.id = 69;
	test_struct.data[0] = 'A';
	test_struct.data[1] = 'A';
	test_struct.data[2] = 'A';
	test_struct.data[3] = 'A';
	test_struct.data[4] = 'A';
	test_struct.data[5] = 'A';
	test_struct.data[6] = 'A';
	test_struct.data[7] = 'A';
	test_struct.length = 8;
	
	
	//message test_struct2;
	//test_struct.id = 420;
	//test_struct.data[0] = 'X';
	//test_struct.data[1] = 'D';
	//test_struct.data[2] = 'd';
	//test_struct.length = 3;
	

	printf("Interupt er ikke aktiv = HOY!\r\n");
	_delay_ms(5000);		
	printf("Interupt er aktiv = LAV!\r\n");
	can_send(test_struct);
	


	

	
	//message test_struct;
	//test_struct.id =0b01;
	//test_struct.length = 8;
	
	//while(1){
	////menu_function();
	//ss_select();
	//mcp2515_read(0b00001111);
	//spi_recieve();
	//ss_deselect();
	//}
}