#include <avr/io.h>
#include "uart.h"
#include "adc_driver.h"
#include "xmem.h"
#include "oled.h"
#include "oled_menu.h"
#include "button_init.h"
#include "spi_driver.h"
#include "mcp2512.h"

#define F_CPU 4915200 // Clock Speed

#include <util/delay.h>
#include <stdio.h>
#include "oled.h"

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
	
	
	spi_master_init();
	
	mcp2515_init();
	
	
	
	mcp2515_write(MCP_CANCTRL,MODE_LOOPBACK);
	ss_select();
	mcp2515_read(0b00001111);
	spi_recieve();
	ss_deselect();
	
	//while(1){
	////menu_function();
	//ss_select();
	//mcp2515_read(0b00001111);
	//spi_recieve();
	//ss_deselect();
	//}
}