/*
 * init.h
 *
 * Created: 16.09.2022 10:57:33
 *  Author: petteroj
 */ 


#ifndef INIT_H_
#define INIT_H_

#define FOSC 4915200 // Clock Speed
#define BAUD 9600 // Baud rate


void adc_timer(); // Clock signal for ADC timer, inherited from the ATmega162 


#endif /* INIT_H_ */