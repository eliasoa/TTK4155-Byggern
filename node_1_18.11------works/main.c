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
#include "joystic_driver.h"

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
	
	printf("\r\n################ Init complete ################\r\n");

	while(1){
		_delay_ms(100);
		send_multifunc_board();
		menu_function();

	};
}