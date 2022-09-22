#include <avr/io.h>
#include "init.h"
#include<util/delay.h>
#include<avr/interrupt.h>

#define OCR0_VALUE 1


void adc_timer(){
	DDRD |= (1 << PD5); 
	TCCR1A=(1 << COM1A0);			 	 // Toggle-mode
	TCCR1B= (1 << WGM12)|(1 << CS10);	 // CTSmode, No scaler
	OCR0= 1; // Put OCR value
}