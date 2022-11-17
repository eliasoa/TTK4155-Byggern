#include "solenoid.h"
#include "delay.h"
#include "sam.h"


void solenoid_init( void)
{	
	//PMC->PMC_PCDR0 |= PMC_PCER_PB
	// Enable IOs for PIN22
	PIOB -> PIO_PER |= PIO_PB26;
	// Set PIN22 as output
	PIOB -> PIO_OER |= PIO_PB26;
	// Enable pull-up
	PIOB -> PIO_PUDR = (PIO_PB26);
	// Setting PIN22 low
	PIOB -> PIO_SODR = PIO_PB26;
}

