#define F_CPU 4915200 // Clock Speed

#include <util/delay.h>
#include <stdio.h>
#include "joystic_driver.h"
#include "adc_driver.h"
#include "can_driver.h"


void send_multifunc_board( void ){
	
	uint8_t y_axis = joystick_analog_position_percentage(read_adc(0),0);
	uint8_t x_axis = joystick_analog_position_percentage(read_adc(1),1);
	uint8_t right_slider = read_adc(2);
	uint8_t left_slider = read_adc(3);
	uint8_t joy_button = (PINB & (1<<PB2));
	uint8_t right_button = (PINB & (1<<PB1));
	uint8_t left_button = (PINB & (1<<PB0));
	
	message multifunc_board_msg;
	multifunc_board_msg.id = 6; //Find good real value
	multifunc_board_msg.length = 7; // Find real length
	multifunc_board_msg.data[0] = y_axis;
	multifunc_board_msg.data[1] = x_axis;
	multifunc_board_msg.data[2] = right_slider;
	multifunc_board_msg.data[3] = left_slider;
	multifunc_board_msg.data[4] = joy_button;
	multifunc_board_msg.data[5] = right_button;
	multifunc_board_msg.data[6] = left_button;
	
	can_send(multifunc_board_msg);
	printf("\r\n####### NEW MESSAGE SENDT #######\r\n");
	printf("Data Y:\t%i\r\n",multifunc_board_msg.data[0]);
	printf("Data X:\t%i\r\n",multifunc_board_msg.data[1]);
	printf("Data Right slider:\t%i\r\n",multifunc_board_msg.data[2]);
	printf("Data Left slider:\t%i\r\n",multifunc_board_msg.data[3]);
	printf("Joy button:\t%i\r\n",multifunc_board_msg.data[4]);
	printf("Right button:\t%i\r\n",multifunc_board_msg.data[5]);
	printf("Left button:\t%i\r\n",multifunc_board_msg.data[6]);
	printf("Data lengt:\t%d\n\r",multifunc_board_msg.length);
	printf("ID:\t%d\r\n",multifunc_board_msg.id);
}