#define F_CPU 4915200 // Clock Speed
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "can_driver.h"
#include "mcp2512.h"

void can_init(){
	mcp2515_init();
	
	mcp2515_write(CANCTRL,MODE_LOOPBACK);	// Loopback
	mcp2515_write(CANINTE,0xFF);			// Interrupt enable
	mcp2515_write(RXB0CTRL, 0xFF);			// Receiver buffer 0 control
	
}