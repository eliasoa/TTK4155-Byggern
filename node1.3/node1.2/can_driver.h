#pragma once
#include <avr/interrupt.h>




typedef struct {
	uint16_t id;
	uint8_t length;
	char data[8];	
	} message;
	
message message1;
message message2;

void can_init();
void  can_send();
message can_receive( uint8_t buffer );