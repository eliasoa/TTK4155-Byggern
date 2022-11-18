#include "sam.h"
#include "motor_driver.h"
#include "dac_driver.h"
#include "delay.h"
#include "pwm_driver.h"
#include "PID.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MOTOR_DIR		PIO_PD10
#define MOTOR_EN		PIO_PD9
#define MOTOR_SEL		PIO_PD2
#define MOTOR_NOT_RST	PIO_PD1
#define MOTOR_NOT_OE	PIO_PD0


// MJ1 INPUT, we must define as output
// NOT_OE = 3
// NOT_RST = 4
// SEL = 5
// EN = 6
// DIR = 7

// MJ2 OUTPUT, we must define as input
// D00 = 3
// ...
// D07 = 10


void motor_box_init(){

	// Give clock to PIOD
	PMC -> PMC_PCER0 = PMC_PCER0_PID14;
	// Enable PIOD for GPIO
	PIOD -> PIO_PER |= MOTOR_DIR | MOTOR_EN | MOTOR_SEL | MOTOR_NOT_RST | MOTOR_NOT_OE;
	// Set pins as output
	PIOD -> PIO_OER |= MOTOR_DIR | MOTOR_EN | MOTOR_SEL | MOTOR_NOT_RST | MOTOR_NOT_OE;
	
	// Give clock to PIOC
	PMC -> PMC_PCER0 = PMC_PCER0_PID13;
	// Enable PIOC for GPIO
	PIOC -> PIO_PER |= PIO_PC1|PIO_PC2|PIO_PC3|PIO_PC4|PIO_PC5|PIO_PC6|PIO_PC7|PIO_PC8;
	// Set pins as input
	PIOC -> PIO_IER |= PIO_PC1|PIO_PC2|PIO_PC3|PIO_PC4|PIO_PC5|PIO_PC6|PIO_PC7|PIO_PC8;
	
	// Set thing in start position
	
	PIOD -> PIO_SODR = MOTOR_EN;
	PIOD -> PIO_SODR = MOTOR_DIR;
	printf("\r\nMoving trolley to start position\n\r");
	dac_write(100);
	delay_us(5000000);

	PIOD -> PIO_CODR = MOTOR_EN;
	printf("\r\nTrolley in position\n\r");	
}

bool direction;


void motor_dir(int16_t u){
	
	// Need to have logic that decides direction
	
	if (u > 0){
		direction = true;
	}
	else if (u < 0)
	{
		direction = false;
	}
	

	
	if (direction == false)
	{
		PIOD -> PIO_SODR = MOTOR_EN;
		PIOD -> PIO_SODR = MOTOR_DIR;

		dac_write(u);
	}
	else if (direction == true)
	{
		PIOD -> PIO_SODR = MOTOR_EN;
		PIOD -> PIO_CODR = MOTOR_DIR;

		dac_write(u);
	}
	else{
		PIOD -> PIO_CODR = MOTOR_EN;
	}
		//printf("%d\n\r",dir);
}

void motor(uint16_t speed){
	//PIOD -> PIO_SODR = MOTOR_EN;
	//PIOD -> PIO_SODR = MOTOR_DIR;
	// PIOD -> PIO_CODR = MOTOR_EN; //Motor stop 
	//dac_write(speed);
}

int16_t encoder(){
	//Set !OE low, to sample and hold the encoder value
	PIOD -> PIO_CODR = MOTOR_NOT_OE;	
				
	//Set SEL low to output high byte
	PIOD -> PIO_CODR = MOTOR_SEL;					
	
	//delay 25 microseconds
	delay_us(20);                                      
	//(PIO_PC1|PIO_PC2|PIO_PC3|PIO_PC4|PIO_PC5|PIO_PC6|PIO_PC7|PIO_PC8)) >> 1
	
	
	int16_t  high_byte =  (PIOC->PIO_PDSR & ((PIO_PC1|PIO_PC2|PIO_PC3|PIO_PC4|PIO_PC5|PIO_PC6|PIO_PC7|PIO_PC8)));
	//printf(high_byte);
	
	//Set SEL high to output low byte
	PIOD -> PIO_SODR = MOTOR_SEL;					 
	
	//delay 20 microseconds
	delay_us(20);                                       
 
	int16_t low_byte = (PIOC->PIO_PDSR & (0x1FE));
	
	//Set !OE high
	PIOD -> PIO_SODR = MOTOR_NOT_OE;				         
	// Combine high and low byte
	
	PIOD ->PIO_SODR = MOTOR_NOT_RST;
	int16_t encoder_value = ((high_byte << 8) | low_byte); 
	
	
	 
	if(encoder_value & (1 << 15)) 
	{
		encoder_value = -((uint16_t) (~encoder_value) +1);	
	}

	return encoder_value;
}