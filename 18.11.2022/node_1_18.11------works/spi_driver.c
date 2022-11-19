#include <avr/io.h>
#include <stdio.h> 
#define F_CPU 4915200 // Clock Speed

#include <util/delay.h>

void ss_select ( void ){
	PORTB &= (~(1 << PB4));
}

void ss_deselect ( void ){
	PORTB |= (1 << PB4);
}

void spi_master_init(void)
{
	// Set MOSI and SCK output, all others input 
	DDRB = (1<<PB4)|(1<<PB5)|(1<<PB7);
	// Enable SPI, Master, set clock rate fck/16 
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); // Tror vi er i SPI mode 0, fordi CPOL og CPHA = 0
	

}
void spi_transmit (char cData)
{
	// Start transmission 
	SPDR = cData;
	// Wait for transmission complete 
	while(!(SPSR & (1<<SPIF)))
	;
}

char spi_recieve( void )
{
	SPDR = 0xFF;
	// Wait for reception complete 
	while(!(SPSR & (1<<SPIF)))
	;
	return SPDR;
}

