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
	
	printf("\r\n################ HELLO ################\r\n");
	
	//message test_struct;
 	//test_struct.id = 2;
 	//test_struct.data[0] = 'A';
 	//test_struct.data[1] = 'b';
 	//test_struct.data[2] = 'c';
 	//test_struct.data[3] = 'd';
 	//test_struct.data[4] = 'e';
 	//test_struct.data[5] = 'f';
 	//test_struct.data[6] = 'g';
 	//test_struct.data[7] = 'h';
 	//test_struct.length = 4;
	
	

	
	while(1){
		_delay_ms(10);
		send_joy_pos();
		//printf("ADC Xanalog:\t%i\r\n",read_adc(0));
		//printf("ADC Xprosent:\t%i\r\n",joystick_analog_position_percentage(read_adc(0),0));
		//printf("ADC Y:\t%i\r\n",joystick_analog_position_percentage(read_adc(0),0));
		//prenk
		};





}




	//while(1){
//// 		
//// 		
	//}
	//



	//
	//
   	//message test_struct2;
   	//test_struct2.id = 420;
   	//test_struct2.data[0] = 'B';
   	//test_struct2.data[1] = 'B';	
	//test_struct2.data[2] = 'B';
   	//test_struct2.data[3] = 'B';
   	//test_struct2.data[4] = 'B';
	//test_struct2.data[5] = 'B';
   	//test_struct2.data[6] = 'B';
	//test_struct2.data[7] = 'B';
	//test_struct2.length = 8;
	
	
//	can_send(test_struct2);
