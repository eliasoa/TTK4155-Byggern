#pragma once

#include <avr/io.h>
#include <stdio.h> // To use printf

void spi_master_init( void );
void spi_transmit ( char cData );
char spi_recieve( void );
void ss_select ( void );
void ss_deselect ( void );