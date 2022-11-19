#include "xmem.h"
#include <avr/io.h>
#include <stdio.h> 
#include "fonts.h"
#include <string.h>

#define F_CPU 4915200 // Clock Speed
#include<util/delay.h>


volatile uint8_t* oled_command_address = (uint8_t*)0x1000;
volatile uint8_t* oled_data_address = (uint8_t*)0x1200;


void oled_write_command( uint8_t data ){
	oled_command_address[0] = data; 
}

void oled_write_data( uint8_t data ){
	oled_data_address[0] = data;
}

void oled_clear( void ){
	for (int i = 0; i < 8; i++){
		oled_write_command(0xb0 + i);
		for (int j = 0; j < 128; j++){
			oled_data_address[i] = 0x0;
		}
	}
}

void oled_pos ( uint8_t row, uint8_t column ){
	oled_write_command(0x22);	oled_write_command(row); 	oled_write_command(0x7);		oled_write_command(0x21);	oled_write_command(column); 	oled_write_command(0x7f);
}

void oled_reset ( void ){
	uint8_t row = 0;
	uint8_t column = 0;
	oled_pos(row,column);
	oled_clear();
	oled_pos(row,column);
}

void oled_fill( void ){
	oled_write_command(0xA5);
}

void oled_init( void ){ // Yoinked from OLED data sheet
	oled_write_command(0xae); // display off
	oled_write_command(0xa1); //segment remap
	oled_write_command(0xda); //common pads hardware: alternative
	oled_write_command(0x12);
	oled_write_command(0xc8); //common output scan direction:com63~com0
	oled_write_command(0xa8); //multiplex ration mode:63
	oled_write_command(0x3f);
	oled_write_command(0xd5); //display divide ratio/osc. freq. mode
	oled_write_command(0x80);
	oled_write_command(0x81); //contrast control
	oled_write_command(0x50);
	oled_write_command(0xd9); //set pre-charge period
	oled_write_command(0x21);
	oled_write_command(0x20); //Set Memory Addressing Mode
	oled_write_command(0x02);
	oled_write_command(0xdb); //VCOM deselect level mode
	oled_write_command(0x30);
	oled_write_command(0xad); //master configuration
	oled_write_command(0x00);
	oled_write_command(0xa4); //out follows RAM content
	oled_write_command(0xa6); //set normal display
	oled_write_command(0xaf); // display on
}

void oled_print(char c){
	
	uint8_t table_ascii_index = c - 32; // 32 = (char)' '
	for (int n = 0; n < 5; n++){
		oled_write_data(pgm_read_byte(&(font5[table_ascii_index][n])));
	}
}

void oled_print_arrow ( uint8_t row , uint8_t col )
{
	oled_pos ( row , col );
	oled_write_data(0b00011000 );
	oled_write_data(0b00011000 );
	oled_write_data(0b01111110 );
	oled_write_data(0b00111100 );
	oled_write_data(0b00011000 );
}

void oled_printf (char* string){
	uint8_t length = strlen(string);
	
	for (int i = 0; i < length; i++){
		oled_print(string[i]);
	}
}

