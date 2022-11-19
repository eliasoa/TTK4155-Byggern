#include "adc_driver.h"
#include "xmem.h"
#include <avr/io.h>
#include <stdio.h> 

#define F_CPU 4915200 // Clock Speed
#include<util/delay.h>

#define OCR0_VALUE 1

// Timer for the ADC
void adc_timer(){						 
	DDRD |= (1 << PD5); 
	// Toggle-mode
	TCCR1A=(1 << COM1A0);			 	 
	// CTSmode, No scaler
	TCCR1B= (1 << WGM12)|(1 << CS10);	 
	// Put OCR value
	OCR0= 1;							 
}

uint8_t read_adc(uint8_t channel){
	// Define data array for storing ADC channels
	uint8_t data [4];					
	// Sends WR and CS to initiate conversion. Writes to ADC using Mux mode 0.
	xmem_write(0x1400,0x00,0x00);		
	// Calculates conversion time given by the data sheet
	uint8_t t_conv = 50;				
	// Wait the conversion time
	_delay_us(t_conv);					
	
	for (uint8_t i = 0; i < 4; i++){
		// Reads through the 4 channels(Mux mode 0) from the ADC and stores them in the data array
		data[i] = xmem_read(0x1400,0x00);	
	}
	// Returns the chosen channel from 0-3
	switch (channel){						
	case 0:	// y-axis
		return data[0];
		break;
	case 1:	// x-axis
		return data[1];
		break;
	case 2:	// Right slider
		return data[2];
		break;
	case 3:	// Left slider
		return data[3];
		break;
	}	
	return 0;
} 

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	// code from https://www.arduino.cc/reference/en/language/functions/math/map/
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//Function that returns joystick position in percentage from neutral. Inputs analog value and chosen channel
 uint8_t joystick_analog_position_percentage (uint8_t analog_value, uint8_t channel){		
	// Defines remapped variable
	signed int remapped;																	
	// Which channel to map
	if (channel == 0){																		
		// Decides which side of joystick neutral to map
		if (analog_value >= 167){	
		// Stores mapping to variable														
		remapped = map(analog_value, 160, 255, 50, 100);									
		}
		else if (analog_value == 0){
			remapped = 0;
		}
		else{
			remapped = map(analog_value, 0, 159, 0, 50);									
		}	
	}
	else if(channel == 1){
		//Decides which side of joystick neutral to map
		if (analog_value >= 167){															
		remapped = map(analog_value, 163, 255, 50, 100);									
		}
		else{
			remapped = map(analog_value, 0, 162, 0, 50);									
		}	
	}
	else if(channel == 2){
		remapped = map(analog_value, 10, 255, 0, 100);										
	}
	else if(channel == 3){
		remapped = map(analog_value, 12, 255, 0, 100);										
	}
	else{
		return 0;										
	}
	// Returns variable, based on the if-statements
	return remapped;																	
}
// Function that returns joystick direction(UP, DOWN, LEFT,RIGHT) as a enum. Input is analog value and desired channel
Joystick_position Joystick_direction ( uint8_t analog_value, uint8_t channel ){			
	// Decides which channel to proceed with (channel 0)
	if (channel == 0){		
		// Choosing which direction to return, based on defined thresholds															
		if (analog_value >= 180)														
		{
			return RIGHT;
		}
		else if (analog_value <= 150)
		{
			return LEFT;
		}
		else {
			return NEUTRAL;
		}
	}
	// Decides which channel to proceed with (channel 1)
	if (channel == 1){		
		// Choosing which direction to return, based on defined tHresholds															
		if (analog_value >= 180)														
		{
			return UP;
		}
		else if (analog_value <= 150)
		{
			return DOWN;
		}
		else {
			return NEUTRAL;
		}
	}
	return 0;
};