#include "adc_driver.h"
#include "xmem.h"
#include <avr/io.h>
#include <stdio.h> // To use printf

#define F_CPU 4915200 // Clock Speed
#include<util/delay.h>

#define OCR0_VALUE 1

void adc_timer(){						 // Timer for the ADC
	DDRD |= (1 << PD5); 
	TCCR1A=(1 << COM1A0);			 	 // Toggle-mode
	TCCR1B= (1 << WGM12)|(1 << CS10);	 // CTSmode, No scaler
	OCR0= 1;							 // Put OCR value
}

uint8_t read_adc(uint8_t channel){
	uint8_t data [4]; // Define data array for storing ADC channels
	xmem_write(0x1400,0x00,0x00); // Sends WR and CS to initiate conversion. Writes to ADC using Mux mode 0.
	uint8_t t_conv = 50; // Calculates conversion time given by the data sheet
	_delay_us(t_conv); // Wait the conversion time
	
	for (uint8_t i = 0; i < 4; i++){
		data[i] = xmem_read(0x1400,0x00); // Reads through the 4 channels(Mux mode 0) from the ADC and stores them in the data array
	}
	switch (channel){					// Returns the choosed channel from 0-3
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

signed int joystick_analog_position_percentage (uint8_t analog_value, uint8_t channel){		//Function that returns joystick position in percentage from neutral. Inputs analog value and chosed channel
	signed int remapped;																	// Defines remapped variable
	if (channel == 0){																		// If-statement choosing which channel to map
		if (analog_value >= 167){															// If-statement that decides which side of joystick neutral to map
		remapped = map(analog_value, 167, 255, 0, 100);										// Stores mapping to variable
		}
		else{
			remapped = map(analog_value, 5, 166, -100, 0);									// Stores mapping to variable
		}	
	}
	else if(channel == 1){
		if (analog_value >= 167){															// If-statement that decides which side of joystick neutral to map
		remapped = map(analog_value, 163, 255, 0, 100);										// Stores mapping to variable
		}
		else{
			remapped = map(analog_value, 5, 162, -100, 0);									// Stores mapping to variable
		}	
	}
	else if(channel == 2){
		remapped = map(analog_value, 10, 255, 0, 100);										// Stores mapping to variable
	}
	else if(channel == 3){
		remapped = map(analog_value, 12, 255, 0, 100);										// Stores mapping to variable
	}
	else{
		return 0;										
	}
	return remapped;																		// Returns variable, based on the if- statements
}

Joystick_position Joystick_direction ( uint8_t analog_value, uint8_t channel ){			// Function that returns joystick direction(UP, DOWN, LEFT,RIGHT) as a enum. Input is analog value and desired channel
	if (channel == 0){																	// If-statement that decides which channel to proceed with (channel 0)
		if (analog_value >= 180)														// If statement choosing which direction to return, based on defined thresholds
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
	if (channel == 1){																	// If-statement that decides which channel to proceed with (channel 1)
		if (analog_value >= 180)														// If statement choosing which direction to return, based on defined tHresholds
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