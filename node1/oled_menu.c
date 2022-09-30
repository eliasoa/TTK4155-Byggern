#include "oled_menu.h"
#include "adc_driver.h"
#include "oled.h"
#define F_CPU 4915200 // Clock Speed

#include <util/delay.h>
#include <stdio.h>
#include "oled.h"

#define BAUD 9600 // Baud rate

//typedef enum {
	//Main_Menu_enum,
	//Start_Game_enum,
	//Settings_enum,
	//Something_enum,
//} Main_menu_display;

uint8_t current_row = 0;
uint8_t Menu_selector = 0;
uint8_t button_state = 0;

void menu_selection(){
	if (current_row == 4 && button_state > 200)
	{
		Menu_selector = 1; // settings
	}
}

void menu_joystick(){
	
	Joystick_position dir = Joystick_direction(read_adc(1),  1);
	button_state = read_adc(2);
	if (dir == UP)
	{
		current_row -= 1;
		//oled_reset();
		oled_print_arrow(current_row,0);
	}
	else if (dir == DOWN)
	{
		current_row += 1;
		//oled_reset();
		oled_print_arrow(current_row,0);
	}
	else
	{
		//oled_reset();
		oled_print_arrow(current_row,0);
	}
	_delay_ms(100);

}

void menu_function(){
		menu_joystick();
		menu_selection();
		printf("%d \r\n",button_state);
		printf("%d \r\n",current_row);
	//Menu display	
	if ( Menu_selector == 0)
	{
		oled_pos(0,0);
		oled_reset();
		oled_pos(0,20);
		oled_printf("L#TTIS spill");
		oled_pos(1,40);
		oled_printf("Main menu");
		oled_pos(3,40);
		oled_printf("Start game");
		oled_pos(4,40);
		oled_printf("Settings");
	}
	else if (Menu_selector == 1)
	{
		oled_pos(0,0);
		oled_reset();
		oled_pos(0,20);
		oled_printf("L#TTIS spill");
		oled_pos(1,40);
		oled_printf("Settings");
		oled_pos(3,40);
		oled_printf("No settings for you");
		oled_pos(4,40);
		oled_printf("Yes");
	}
}