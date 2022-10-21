#define F_CPU 4915200 // Clock Speed
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "can_driver.h"
#include "mcp2512.h"

uint8_t interrupt_list; 

void can_init( void ){
	mcp2515_init();
	
	DDRB |= (1 << PB3);
	
	mcp2515_write(MCP_CANINTE,0b00000011);		// Enable interrupt on Recieve buffer 0 and 1
	mcp2515_write(MCP_RXB0CTRL, 0xFF);			// Turn filters off
	mcp2515_write(MCP_RXB1CTRL, 0xFF);			// Turn filters off
	mcp2515_write(MCP_CANCTRL,MODE_LOOPBACK);	// Loopback
	
	
	// TODO: Comment what these do
	cli(); 
	MCUCR |= (1<<ISC01);
	MCUCR &= (~(1 << ISC00));
	GICR |= (1<<INT1);
	DDRD &= ~(1 << PD3);
	sei();
	
	
	
	uint8_t val = 1;
	mcp_read_pointer( MCP_CANSTAT, &val );
	
	if ( ( val & MODE_MASK ) == MODE_LOOPBACK )
	{
				printf (" MCP2515 is IN loopback mode after init !\r\n");
	}
	
}




void can_send( message send ){

	mcp2515_write(MCP_TXB0SIDH, send.id&0b11111111000 >> 3);	// id 8/11 bits
	mcp2515_write(MCP_TXB0SIDL, send.id&111 << 5);			    // id 3/11 bits from LSB
	
	mcp2515_write(MCP_TXB0DLC, send.length);					// DLC
	
	for (int i = 0; i < send.length; i++){
		mcp2515_write(MCP_TXB0D0+i, send.data[i]);				// buffer
	}
	
	mcp2515_rts(0);												// Request to send. Sends buffer if available
}



ISR(INT1_vect){
	uint8_t interrupt_list[1] = {0};
	uint8_t interrupt_flag = mcp2515_read(MCP_CANINTF);
	interrupt_list[0] = (interrupt_flag & MCP_RX0IF);	// Checks if Receive Buffer 0 is full by bit masking  01 & 01 = 01
	interrupt_list[1] = (interrupt_flag & MCP_RX1IF);	// Checks if Receive Buffer 1 is full by bit masking  01 & 01 = 01
	
	if (interrupt_list[0]){
		message1 = can_receive(0);
		//printf("I_L 0\r\n");
		printf(message1.data);
		mcp2515_bit_modify(MCP_CANINTF, 0b00000011, 0);
	}
	else if(interrupt_list[1]){
		message2 = can_receive(1);
		printf(message2.data);
		mcp2515_bit_modify(MCP_CANINTF, 2, 0);
	}
}


message can_receive( uint8_t buffer ){
	message receive;
	
	if (buffer == 0){
		uint8_t id_low = mcp2515_read(MCP_RXB0SIDL);			// read id 3/11 bits from LSB
		uint8_t id_high = mcp2515_read(MCP_RXB0SIDH);			// read id 8/11 bits from MSB
		receive.id = (id_high << 3) | (id_low >> 5);
	
		receive.length = mcp2515_read(MCP_RXB0DLC);				// DLC

		for (int i = 0; i < receive.length; i++){
			receive.data[i] = mcp2515_read(MCP_RXB0D0+i);		// read from buffer 0
			}
	}
	
	else if (buffer == 1){
		uint8_t id_low = mcp2515_read(MCP_RXB1SIDL);			// read id 3/11 bits from LSB
		uint8_t id_high = mcp2515_read(MCP_RXB1SIDH);			// read id 8/11 bits from MSB
		receive.id = (id_high << 3) | (id_low >> 5);
		
		receive.length = mcp2515_read(MCP_RXB1DLC);				// DLC

		for (int i = 0; i < receive.length; i++){
			receive.data[i] = mcp2515_read(MCP_RXB1D0+i);		// read from buffer 0
		}
	}
	return receive;
}