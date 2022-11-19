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
	
	// SJW = 1 BRP = 3 -> Baudrate 125 kHz Tq = 500
	mcp2515_write(MCP_CNF1, 0b01000011); 
	// NOE MER PS1 = 6 and PRSEG = 1
	mcp2515_write(MCP_CNF2, 0b10110001); 
	// PS2 = 5
	mcp2515_write(MCP_CNF3, 0b00000101); 
	
	// Enable interrupt on Receive buffer 0 and 1
	mcp2515_write(MCP_CANINTE,0b00000011);		
	_delay_ms(30);
	mcp2515_bit_modify(MCP_CANINTF,0xFF,0x00);
	_delay_ms(30);
	
	// Turn filters off
	mcp2515_write(MCP_RXB0CTRL, 0xFF);			
	// Turn filters off
	mcp2515_write(MCP_RXB1CTRL, 0xFF);			
	
	
	cli();
	//Enable falling edge interrupt request
	MCUCR |= (1<<ISC01);
	MCUCR &= (~(1 << ISC00));
	// External interrupt request 1 enable
	GICR |= (1<<INT1);
	// Define PD3 as interrupt pin
	DDRD &= ~(1 << PD3);
	sei();
	
	_delay_ms(30);
	mcp2515_write(MCP_CANCTRL,MODE_NORMAL);		// Normal
	

	

	
	
	
	uint8_t val = 1;
	mcp_read_pointer( MCP_CANSTAT, &val );
	
	if ( ( val & MODE_MASK ) == MODE_LOOPBACK )
	{
				printf (" MCP2515 is IN loopback mode after init !\r\n");
	}
	if ( ( val & MODE_MASK ) == MODE_NORMAL )
	{
		printf (" MCP2515 is IN NORMAL mode after init !\r\n");
	}	
}




void can_send( message send ){
	// id: 8/11 bits from MSB
	mcp2515_write(MCP_TXB0SIDH, (send.id&0b11111111000) >> 3);	
	// id: 3/11 bits from LSB
	mcp2515_write(MCP_TXB0SIDL, (send.id&0b111) << 5);			    
	// DLC
	mcp2515_write(MCP_TXB0DLC, send.length);					
	
	for (int i = 0; i < send.length; i++){
		// buffer
		mcp2515_write(MCP_TXB0D0+i, send.data[i]);				
	}
	// Request to send. Sends buffer if available
	mcp2515_rts(0);												
}



ISR(INT1_vect){
	uint8_t interrupt_list[1] = {0};
	uint8_t interrupt_flag = mcp2515_read(MCP_CANINTF);
	// Checks if Receive Buffer 0 is full by bit masking  01 & 01 = 01
	interrupt_list[0] = (interrupt_flag & MCP_RX0IF);	
	// Checks if Receive Buffer 1 is full by bit masking  01 & 01 = 01
	interrupt_list[1] = (interrupt_flag & MCP_RX1IF);	
	
	if (interrupt_list[0]){
		message1 = can_receive(0);
		printf("\r\n################# NEW MESSAGE ###########\r\n");
		printf("Received message on buffer 1:\t");
		for (uint8_t i = 0; i < message1.length; i++ )
		{
			printf("%c",message1.data[i]);
		}
		printf("\r\nwith data lengt:\t%d\n\r",message1.length);
		printf("ID:\t%d\r\n",message1.id);
		printf("\r\n");
		mcp2515_bit_modify(MCP_CANINTF, 0b00000001, 0);
	}
	else if(interrupt_list[1]){
		message2 = can_receive(1);
		printf("\r\n################# NEW MESSAGE ###########\r\n");
		printf("Received message on buffer 2:\t");
		for (uint8_t i = 0; i < message2.length; i++ )
		{
			printf("%c",message2.data[i]);
		}
		printf("\r\nwith data lengt:\t%d\n\r",message2.length);
		printf("ID:\t%d\r\n",message2.id);
		printf("\r\n");
		printf("\r\n");
		mcp2515_bit_modify(MCP_CANINTF, 0b00000010, 0);
	}
}


message can_receive( uint8_t buffer ){
	message receive;
	
	if (buffer == 0){
		// read id 3/11 bits from LSB
		uint8_t id_low = 0b11100000 & mcp2515_read(MCP_RXB0SIDL);	
		// read id 8/11 bits from MSB		
		uint8_t id_high = mcp2515_read(MCP_RXB0SIDH);			
		receive.id = (id_high << 3) | (id_low >> 5);
	
		// DLC
		receive.length = mcp2515_read(MCP_RXB0DLC);				

		for (int i = 0; i < receive.length; i++){
			// read from buffer 0
			receive.data[i] = mcp2515_read(MCP_RXB0D0+(uint8_t) i);		
			}
	}
	
	else if (buffer == 1){
		// read id 3/11 bits from LSB
		uint8_t id_low = 0b11100000 & mcp2515_read(MCP_RXB1SIDL);	
		// read id 8/11 bits from MSB		
		uint8_t id_high = mcp2515_read(MCP_RXB1SIDH);			
		receive.id = (id_high << 3) | (id_low >> 5);
		
		// DLC
		receive.length = mcp2515_read(MCP_RXB1DLC);				

		for (int i = 0; i < receive.length; i++){
			// read from buffer 0
			receive.data[i] = mcp2515_read(MCP_RXB1D0+i);		
		}
	}
	return receive;
}