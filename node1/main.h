#include "uart.h"
#ifndef MAIN_H_
#define MAIN_H_


#define F_CPU 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
//#define BASE_ADDRESS 0x1800 // Temp set to the SRAM proposed address

void main(void);



#endif