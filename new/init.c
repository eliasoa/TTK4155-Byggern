#include <avr/io.h>
#include "init.h"
#include<util/delay.h>
#include<avr/interrupt.h>

#define OCR0_VALUE 1


void xmem_init (){
	MCUCR |= (1 << SRE ); // enable XMEM
	SFIOR |= (1 << XMM2 ); // mask unused bits
}

void xmem_write ( uint8_t data , int addr ){
	volatile char * ext_mem = ( char *) BASE_ADDRESS ;
	ext_mem [ addr ]= data ;
}

uint8_t xmem_read ( uint16_t addr ){
	volatile char * ext_mem = ( char *) 0xffff ;
	uint8_t ret_val = ext_mem [ addr ];
	return ret_val ;
}

void adc_timer(){
	DDRD |= (1 << PD5); 
	TCCR1A=(1 << COM1A0);			 	 // Toggle-mode
	TCCR1B= (1 << WGM12)|(1 << CS10);	 // CTSmode, No scaler
	OCR0= 1; // Put OCR value
}