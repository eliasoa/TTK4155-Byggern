#pragma once


typedef struct {
	uint16_t id;
	uint8_t length;
	signed char data[8];
	} Joysick_message;

void send_multifunc_board( void );