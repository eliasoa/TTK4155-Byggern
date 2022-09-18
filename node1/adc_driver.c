/*
 * CFile1.c
 *
 * Created: 18.09.2022 14:35:09
 *  Author: petteroj
 */ 

#include "adc_driver.h"
#include "xmem.h"
#include<util/delay.h>


// TODO: DET ER ET OFFSET PÅ 5121 (0X1400??) PÅ AVLEST VERDI!!!!
int read_adc(int channel){
	int data [4]; // Define data array for storing ADC channels
	xmem_write(0x1400,0x00,0x00); // Sends WR and CS to initiate conversion
	int t_conv = (9*4*2)/4915200; // Calculates conversion time given by the data sheet
	_delay_us(t_conv); // Wait the conversion time
	
	for (int i = 0; i < 4; i++){
		data[i] = xmem_read(0x1400,0x00+i); // Reads through the 4 channels from the ADC and stores them in the data array
	}
	switch (channel){
	case 1:	// y-axis
		return data[0];
		break;
	case 2:	// x-axis
		return data[1];
		break;
	case 3:	// Slider?
		return data[2];
		break;
	case 4:	// Slider?
		return data[3];
		break;
	}	
}