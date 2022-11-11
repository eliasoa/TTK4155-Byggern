#define F_CPU 4915200 // Clock Speed
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "spi_driver.h"
#include "mcp2512.h"



uint8_t mcp2515_read ( uint8_t address ){
	uint8_t data_out;
	ss_select();
	spi_transmit(MCP_READ);
	spi_transmit(address);
	data_out = spi_recieve();
	ss_deselect();
	
	return data_out;
}

void mcp2515_write ( uint8_t address, uint8_t data ) {
	ss_select();
	spi_transmit(MCP_WRITE);
	spi_transmit(address);
	spi_transmit(data);
	ss_deselect();
}

void mcp2515_rts ( uint8_t buffer ){
	ss_select();
	if (buffer == 0)
	{
		spi_transmit(MCP_RTS_TX0);
	}
	else if (buffer == 1)
	{
		spi_transmit(MCP_RTS_TX1);
	}
	else if (buffer == 2)
	{
		spi_transmit(MCP_RTS_TX2);
	}
	ss_deselect();
}

uint8_t mcp2515_read_status ( void ){
	uint8_t data_out;
	ss_select();
	spi_transmit(MCP_READ_STATUS);
	data_out = spi_recieve(); // POSSIBLY PROBLEMS 
	ss_deselect();
	return data_out;
}

void mcp2515_bit_modify ( uint8_t address, uint8_t mask, uint8_t data ){
	ss_select();
	spi_transmit(MCP_BITMOD);
	spi_transmit(address);
	spi_transmit(mask);
	spi_transmit(data);
	ss_deselect();
}

void mcp2515_reset ( void ) {
	ss_select();
	spi_transmit(MCP_RESET);
	ss_deselect();
}

void mcp_read_pointer ( uint8_t address, uint8_t* value ) {
	uint8_t data_out;
	ss_select();
	spi_transmit(MCP_READ);
	spi_transmit(address);
	data_out = spi_recieve();
	ss_deselect();
	
	*value = data_out;
}


uint8_t mcp2515_init ( void ) {
	uint8_t value = 1;
	spi_master_init () ; // Initialize SPI
	mcp2515_reset () ; // Send reset - command
	// Self - test
	mcp_read_pointer ( MCP_CANSTAT, &value );

	if (( value & MODE_MASK ) != MODE_CONFIG ) {
		printf (" MCP2515 is NOT in configuration mode after reset !\r\n");
		return 1;
	}
	else if ( ( value & MODE_MASK ) == MODE_CONFIG )
	{
				printf (" MCP2515 is IN configuration mode after reset !\r\n");
	}
	// More initialization
	return 0;
}
