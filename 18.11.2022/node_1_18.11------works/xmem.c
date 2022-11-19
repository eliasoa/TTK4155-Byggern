#include "xmem.h"
#include <avr/io.h>

//External memory

void xmem_init (){
	MCUCR |= (1 << SRE );								// enable XMEM
	SFIOR |= (1 << XMM2 );								// mask unused bits
}

void xmem_write ( uint16_t base_address, int addr, uint8_t data){
	volatile char * ext_mem = ( char *) base_address ;
	ext_mem [ addr ]= data ;
}

uint8_t xmem_read ( uint16_t base_address, uint16_t addr ){
	volatile char * ext_mem = ( char *) base_address ;	//ADC address
	uint8_t ret_val = ext_mem [ addr ];
	return ret_val ;
}