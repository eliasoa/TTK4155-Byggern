#include "oled_menu.h"
#include "adc_driver.h"
#include "oled.h"
#define F_CPU 4915200 // Clock Speed

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define start_row 3;
// Start row
uint8_t current_row = start_row;		
// Initializing Main menu
uint8_t current_menu = 0;				
uint8_t last_menu = 0;
// Initializing min row limit for Main menu
uint8_t current_row_min = 3;
// Initializing max row limit for Main menu. This is the row for "Back to Menu" selection			
uint8_t current_row_max = 4;			
uint8_t button_state = 0;
// Initializing Default tribute character: "Erik Keith"
uint8_t selected_character = 0;	
// Flag supposed to come from node 2 when game finished. TBI		
uint8_t game_finished = 0;				

#define BAUD 9600 // Baud rate


void menu_selection(){
	// Go to Main menu if in Settings and button pressed on the "Back to menu" row
	if ((current_menu == 2 && current_row == current_row_max && button_state == 0) || game_finished == 1)			
	{	
		//Menu parameters set
		current_menu = 0;				// Main menu
		current_row = start_row;
		current_row_min = 3;
		current_row_max = 4;
		// When returning to Main menu, set low
		trigger_game = 0;				
	}
	// Start game if in Main menu and button pressed on "Start game" row
	else if (current_menu == 0 && current_row == current_row_min && button_state == 0 )	
	{	
		//Menu parameters set
		current_menu = 1;				// Start game
		current_row_min = 3;
		current_row_max = 3;
		// When set high, active game
		trigger_game = 1;			
		
		
	}
	// Go to Settings menu if either in Main menu, OR in Select characters menu
	else if ((current_menu == 0 && current_row == 4 && button_state == 0) || (current_menu == 3 && current_row == 6 && button_state == 0 )) 
	{	//Menu parameters set
		current_menu = 2;				// Settings
		current_row = start_row;
		current_row_min = 3;
		current_row_max = 4;
	}
	// Go to Select character menu if in Settings menu and button pressed on the corresponding row
	else if (current_row == 3 && button_state == 0 && current_menu == 2)					
	{	
		//Menu parameters set
		current_menu = 3;				// Select character
		current_row = start_row;
		current_row_min = 3;
		current_row_max = 6;	
	}
}				

void menu_joystick(){
	Joystick_position dir = Joystick_direction(read_adc(0),  1);
	button_state =!! (PINB & (1 << PINB2));;
	if (dir == UP)
	{
		current_row -= 1;
		// If current row is under min limit, hold at this min
		if  (current_row < current_row_min)						
		{
			current_row = current_row_min;
		}
		oled_print_arrow(current_row,0);

	}
	else if (dir == DOWN)
	{
		current_row += 1;
		// If current row is over max limit, hold at this max
		if  (current_row > current_row_max)						
		{
			current_row = current_row_max;
		}		
		oled_print_arrow(current_row,0);
	}
	else
	{
		oled_print_arrow(current_row,0);
	}
	_delay_ms(100);

}

void menu_select_choice(){
	//Select characters based on row, button state and current menu
	if (current_row == 3 && button_state == 0 && current_menu ==3)			
	{
		selected_character = 1;

	}
	else if (current_row == 4 && button_state == 0 && current_menu ==3)		
	{
		selected_character = 2;

	}
	else if (current_row == 5 && button_state == 0 && current_menu ==3)
	{
		selected_character =3;

	}
}												




void menu_function(){
		menu_joystick();
		menu_selection();
		menu_select_choice();
	//Display menus
	//Main menu
	if ( current_menu == 0)						
	{
		oled_pos(0,0);
		oled_reset();
		oled_pos(0,40);
		oled_printf("PING PONG");
		oled_pos(1,40);
		oled_printf("Main menu");
		oled_pos(3,40);
		oled_printf("Start game");
		oled_pos(4,40);
		oled_printf("Settings");
		//if (game_finished == 1)				//TBI
		//{
		//oled_pos(6,40);
		//oled_printf("Highscore: ");
		//}
		
	}
	//Game running
	if (current_menu == 1)						
	{
		oled_pos(0,0);
		oled_reset();
		oled_pos(3,35);
		oled_printf("GAME RUNNING");
		if (selected_character == 1)
		{
		oled_pos(5,35);
		oled_printf("Sacit playing");
		}
		else if (selected_character == 2)
		{
		oled_pos(5,35);
		oled_printf("Elias playing");
		}
		else if (selected_character == 3)
		{
		oled_pos(5,35);
		oled_printf("P-man playing");
		}
		else
		{
			oled_pos(5,35);
			oled_printf("Erik Keith playing");
		}
	}
	//Settings
	else if (current_menu == 2)					
	{
		oled_pos(0,0);
		oled_reset();
		oled_pos(0,40);
		oled_printf("PING PONG");
		oled_pos(1,40);
		oled_printf("Settings");
		oled_pos(3,40);
		oled_printf("Select character");
		oled_pos(4,40);		
		oled_printf("Back to menu");
	}
	//Chose character
	else if (current_menu == 3)					
	{
		oled_pos(0,0);
		oled_reset();
		oled_pos(0,40);
		oled_printf("PING PONG");
		oled_pos(1,40);
		oled_printf("Select character");
		oled_pos(3,40);
 		if (selected_character == 1)
 		{
			oled_print_arrow(3,30);
 		}		
		oled_printf("Sacit");
		oled_pos(4,40);
		if (selected_character == 2)
		{
			oled_print_arrow(4,30);
		}		
		oled_printf("Elias");
		oled_pos(5,40);
		if (selected_character == 3)
		{
			oled_print_arrow(5,30);
		}
		oled_printf("P-man");
		oled_pos(6,40);
		oled_printf("Back to settings");
	}	
}