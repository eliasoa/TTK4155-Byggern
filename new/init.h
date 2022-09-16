/*
 * init.h
 *
 * Created: 16.09.2022 10:57:33
 *  Author: petteroj
 */ 


#ifndef INIT_H_
#define INIT_H_

//#define BASE_ADDRESS 0x1000 // Temp set to the OLED proposed address  
#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define BASE_ADDRESS 0x1000 // Temp set to the OLED proposed address





void xmem_init ();

//void xmem_write ( uint8_t data ,int addr );

uint8_t xmem_read ( uint16_t addr );

void wave_square();


#endif /* INIT_H_ */