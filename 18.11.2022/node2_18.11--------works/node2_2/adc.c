#include "adc_driver.h"
#include "sam.h"

uint16_t score = 0;

void adc_init(){
	// Enable clock for ADC: ADC_ID = 37, PCER1_ID=37 = 5 -> 37-32
	PMC -> PMC_PCER1 |= PMC_PCER1_PID37;
	// Skal ikke være nødvendig, siden enabling av channel skal gjøre dette
	//	PIOA ->PIO_PER |= PMC_PCER1_PID37;
	
	
	// Enable channel 0 (AD0 peripheral)
	ADC -> ADC_CHER |= ADC_CHER_CH7;
	
	// Set ADC mode, FREERUN = never wait for trigger -> ADC converts all the time
	ADC -> ADC_MR |= ADC_MR_FREERUN;
	
	
	
	// Start conversion 
	//ADC -> ADC_CR |= ADC_CR_START;
}


uint16_t adc_read(){
		// Read ADC channel 0
		//while (!ADC_ISR_EOC7){}
			
		return ADC -> ADC_CDR[7];
}

uint16_t ir_counter(uint16_t value)
	{
	uint16_t ir_limit = 200;
	if (value < ir_limit)
	{
		score +=1;
		return score;
	}
	return score;
}