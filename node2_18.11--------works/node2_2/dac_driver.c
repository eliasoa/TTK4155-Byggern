#include "sam.h"
#include "dac_driver.h"

void dac_init(){
	
	// Enable clock for DAC
	PMC -> PMC_PCER1 |= PMC_PCER1_PID38;
	// Enable DAC channel 1
	DACC -> DACC_CHER |= DACC_CHER_CH1;	
	// Set DAC startup time to 0, free running mode and half-word transfer, refresh
	DACC -> DACC_MR |= DACC_MR_STARTUP_0 | DACC_MR_TRGEN_DIS | DACC_MR_WORD_HALF | DACC_MR_REFRESH(0x1);
	// Select channel 1
	DACC ->DACC_MR |=DACC_MR_USER_SEL_CHANNEL1;
}

void dac_write( uint16_t value){
	// Map value from 0 - 255 to 0 - 4095 (12 bit not 16?)
	uint16_t val = (uint16_t)value*4095/255;
	DACC -> DACC_CDR = val;
}


