#include "solenoid.h"
#include "delay.h"
#include "sam.h"

//message.data[4]



void solenoid_init( void)
{
	// Enable IOs for PIN22
	PIOB -> PIO_PER = PIO_PB26;
	// Set PIN22 as output
	PIOB -> PIO_OER = PIO_PB26;
	// Disable pull-up
	PIOB -> PIO_PUDR = PIO_PB26;
	// Setting PIN22 low
	PIOB -> PIO_SODR = PIO_PB26;
}

void solenoid_trigger(int button)
{
	if ( button == 0)
	{
		PIOB -> PIO_CODR = PIO_PB26;			//Set high
		delay_us(1000);
		PIOB ->PIO_SODR = PIO_PB26;				//Set low
	}
}