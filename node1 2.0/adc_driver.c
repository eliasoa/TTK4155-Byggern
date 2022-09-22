/*
 * CFile1.c
 *
 * Created: 18.09.2022 14:35:09
 *  Author: petteroj
 */ 

#include "adc_driver.h"
#include "xmem.h"
#include<util/delay.h>

struct Multiboard {
	uint8_t x_axis; 
	uint8_t y_axis;
	uint8_t slider_right;
	uint8_t slider_left;
	
	};

			struct Multiboard Multiboard_1;		//Defines a struct object and a type

	

// TODO: DET ER ET OFFSET PÅ 5121 (0X1400??) PÅ AVLEST VERDI!!!!
	struct Multiboard read_adc(int channel){
		

			int t_conv = (9*4*2)/4915200; // Calculates conversion time given by the data sheet
			
			
			xmem_write(0x1400,0x00,0b10000000); // Sends WR, CS and mux address to initiate conversion
			_delay_us(t_conv); // Wait the conversion time
			Multiboard_1.x_axis = xmem_read(0x1400,0x000); // Reads through the 4 channels from the ADC and stores them in the data array
			_delay_us(t_conv); // Wait the conversion time
			
			//Channel 1
			xmem_write(0x1400,0x00,0b10000001); // Sends WR, CS and mux address to initiate conversion
			_delay_us(t_conv); // Wait the conversion time
			Multiboard_1.y_axis = xmem_read(0x1400,0x001); // Reads through the 4 channels from the ADC and stores them in the data array
			_delay_us(t_conv); // Wait the conversion time

			//Channel 2
			xmem_write(0x1400,0x00,0b10000010); // Sends WR, CS and mux address to initiate conversion
			_delay_us(t_conv); // Wait the conversion time
			Multiboard_1.slider_right = xmem_read(0x1400,0x002); // Reads through the 4 channels from the ADC and stores them in the data array
			_delay_us(t_conv); // Wait the conversion time
			

			//Channel 3
			xmem_write(0x1400,0x00,0b10000011); // Sends WR, CS and mux address to initiate conversion
			_delay_us(t_conv); // Wait the conversion time
			Multiboard_1.slider_left = xmem_read(0x1400,0x003); // Reads through the 4 channels from the ADC and stores them in the data array
			
			uint8_t dataa = Multiboard_1.slider_left;
			return Multiboard_1;
		
		
		
		
		
		


// 	switch (channel){
// 		case 1:	// -axis
// 			//Channel 0
// 			xmem_write(0x1400,0x00,0b00000000); // Sends WR, CS and mux address to initiate conversion
// 			_delay_us(t_conv); // Wait the conversion time
// 			Multiboard_1.x_axis = xmem_read(0x1400,0x000); // Reads through the 4 channels from the ADC and stores them in the data array
// 			return Multiboard_1.x_axis;
// 			break;
// 			
// 		case 2:	// x-axis
// 			//Channel 1
// 			xmem_write(0x1400,0x00,0b00000000); // Sends WR, CS and mux address to initiate conversion
// 			_delay_us(t_conv); // Wait the conversion time
// 			Multiboard_1.y_axis = xmem_read(0x1400,0x001); // Reads through the 4 channels from the ADC and stores them in the data array
// 			return Multiboard_1.y_axis;
// 			break;
// 			
// 		case 3:	// Slider right
// 			//Channel 2
// 			xmem_write(0x1400,0x00,0b00000000); // Sends WR, CS and mux address to initiate conversion
// 			_delay_us(t_conv); // Wait the conversion time
// 			Multiboard_1.slider_right = xmem_read(0x1400,0x002); // Reads through the 4 channels from the ADC and stores them in the data array
// 			return Multiboard_1.slider_right;
// 			break;		
// 		
// 		case 4:	// Slider left
// 			//Channel 3
// 			xmem_write(0x1400,0x00,0b00000000); // Sends WR, CS and mux address to initiate conversion
// 			_delay_us(t_conv); // Wait the conversion time
// 			Multiboard_1.slider_left = xmem_read(0x1400,0x003); // Reads through the 4 channels from the ADC and stores them in the data array
// 			return Multiboard_1.slider_left;
// 			break;
// 		
// 		
//		}
	}
	