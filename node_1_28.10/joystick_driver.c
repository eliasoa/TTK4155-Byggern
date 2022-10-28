#define F_CPU 4915200 // Clock Speed

#include <util/delay.h>
#include <stdio.h>
#include "joystic_driver.h"
#include "adc_driver.h"
#include "can_driver.h"





void send_joy_pos( void ){
	
	uint8_t y_axis = joystick_analog_position_percentage(read_adc(0),0);
	uint8_t x_axis = joystick_analog_position_percentage(read_adc(1),1);
	
	message joy_analog_pos_msg;
	joy_analog_pos_msg.id = 6; //Find good real value
	joy_analog_pos_msg.length = 4; // Find real length
	joy_analog_pos_msg.data[0]= y_axis;
	joy_analog_pos_msg.data[1]= x_axis;

	
	can_send(joy_analog_pos_msg);
	printf("\r\n####### NEW MESSAGE SENDT #######\r\n");
	printf("Data Y:\t%i\r\n",joy_analog_pos_msg.data[0]);
	printf("Data X:\t%i\r\n",joy_analog_pos_msg.data[1]);
	printf("Data lengt:\t%d\n\r",joy_analog_pos_msg.length);
	printf("ID:\t%d\r\n",joy_analog_pos_msg.id);
}

//void send_joy_dir( void ){
	//
//}