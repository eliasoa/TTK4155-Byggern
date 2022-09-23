/*
If the signal from A0 is different before and after the d-latch, but equal at the pinout for A0, the shit works
*/



#include "UART_driver.h"

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#define BASE_ADDRESS 0x1800 // Temp set to the SRAM proposed address  

unsigned char tall = 'y';
//unsigned char tall = 0b10000001;

void main(void)
{
	//UART_Init(MYUBRR);
	xmem_init();
	int data = 0b00001110;
	int addr = 0b1;

	// Set pins A and E to outputs
	//DDRA = 0b11111111;
	//DDRE = 0b11111111;

   while (1)
   {
		xmem_write(data, addr);
		//xmem_read(addr);
		//printf(data);
   }
}


void DLatch_test()
{
	PORTE |= (1 << 1); // Setting ALE to high
	PORTA |= (1 << 7); // Setting port high
}

void xmem_init ( void ){
	MCUCR |= (1 << SRE ); // enable XMEM
	SFIOR |= (1 << XMM2 ); // mask unused bits
}

void xmem_write ( uint8_t data , uint16_t addr ){
	volatile char * ext_mem = ( char *) BASE_ADDRESS ;
	ext_mem [ addr ]= data ;
}

uint8_t xmem_read ( uint16_t addr ){
	volatile char * ext_mem = ( char *) BASE_ADDRESS ;
	uint8_t ret_val = ext_mem [ addr ];
	return ret_val ;
}
