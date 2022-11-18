#pragma once
#include <avr/io.h>
#include <stdio.h> // To use printf
#include <avr/io.h>

//uint8_t Start_game = 0;
//uint8_t Settings = 1;
//uint8_t Something = 2;
//uint8_t current_row = 0;
//uint8_t Menu_selector = 0;

uint8_t trigger_game;				// Set to high when game is starting


void menu_function();
