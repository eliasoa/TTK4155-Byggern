#include <avr/io.h>
#include "uart.h"
#include "adc_driver.h"
#include "xmem.h"
#include "oled.h"
#include "oled_menu.h"

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
	adc_timer();
	UART_Init();
	oled_init();
	oled_clear();
	_delay_ms(1000);
	uint8_t row = 0;
	uint8_t column = 0;
	oled_pos(row,column);
	//char* string;
	//DDRB &= ~ ((1<<PB0)|(1<<PB1));
	
	//DDRB = 0x00; // all B ports as input
	//PORTB=0xFF; //	internal pull up
	//DDRB &= ~((1<<PD0)|(1<<PD1)|(1<<PD2));

	
	while(1){
	menu_function();
	}                     
}