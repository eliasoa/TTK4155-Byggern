#include "oled_menu.h"
#include "adc_driver.h"
#include "oled.h"
#define F_CPU 4915200 // Clock Speed

#include <util/delay.h>
#include <stdio.h>
#include "oled.h"

#define BAUD 9600 // Baud rate

// /typedef enum {						// Enum for Main menu choices
// 	Main_Menu = 0,
// 	Start_Game,
// 	Settings,
// } Main_menu_display;
// 
// /typedef enum{						// Enum for Settings choices
// 	Select_character = 3,
// 	Something_other,
// } Settings_menu_display;


#define start_row 3;
uint8_t current_row = start_row;		// Start row 
uint8_t current_menu = 0;				// Initializing Main menu
uint8_t last_menu = 0;
uint8_t current_row_min = 3;			// Initializing min row limit for Main menu
uint8_t current_row_max = 4;			// Initializing max row limit for Main menu. This is the row for "Back to Menu" selection
uint8_t button_state = 0;
uint8_t selected_character = 0;			// Initializing Default character "Erik Keith"

void menu_selection(){
	if (current_menu == 2 && current_row == current_row_max && button_state > 200)			// Go to Main menu if in Settings and button pressed on the "Back to menu" row
	{
		current_menu = 0;				// Main menu
		current_row = start_row;
		current_row_min = 3;
		current_row_max = 4;
	}
	else if (current_menu == 0 && current_row == current_row_min && button_state > 200 )	// Start game if in Main menu and button pressed on "Start game" row
	{
		current_menu = 1;				// Start game
	}
	
	else if ((current_menu == 0 && current_row == 4 && button_state > 200) || (current_menu == 3 && current_row == 6 && button_state > 200 )) // Go to Settings menu if either in Main menu, OR in Select characters menu
	{
		current_menu = 2;				// Settings
		current_row = start_row;
		current_row_min = 3;
		current_row_max = 6;
	}
	else if (current_row == 4 && button_state > 200 && current_menu == 2)					// Go to Select character menu if in Settings menu and button pressed on the corresponding row
	{
		current_menu = 3;				// Select character
		current_row = start_row;
		current_row_min = 3;
		current_row_max = 6;	
	}
}				

void menu_joystick(){
	
	Joystick_position dir = Joystick_direction(read_adc(1),  1);
	button_state = read_adc(2);
	if (dir == UP)
	{
		current_row -= 1;
		if  (current_row < current_row_min)						// If current row is under min limit, hold at this min
		{
			current_row = current_row_min;
		}
		//oled_reset();
		oled_print_arrow(current_row,0);

	}
	else if (dir == DOWN)
	{
		current_row += 1;
		if  (current_row > current_row_max)						// If current row is over max limit, hold at this max
		{
			current_row = current_row_max;
		}		
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

void menu_select_choice(){
	if (current_row == 3 && button_state > 200)
	{
		selected_character = 1;

	}
	else if (current_row == 4 && button_state > 200)
	{
		selected_character = 2;

	}
	else if (current_row == 5 && button_state > 200)
	{
		selected_character =3;

	}
}												// Function for selecting specific settings 




void menu_function(){
		menu_joystick();
		menu_selection();
		menu_select_choice();
		printf("%d \r\n",button_state);
		printf("%d \r\n",current_row);
	//Menu display	
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
	}
	else if (current_menu == 2)
	{
		oled_pos(0,0);
		oled_reset();
		oled_pos(0,40);
		oled_printf("PING PONG");
		oled_pos(1,40);
		oled_printf("Settings");
		oled_pos(3,40);
		oled_printf("No!");
		oled_pos(4,40);
		oled_printf("Select character");
		oled_pos(5,40);
		oled_printf("No settings3");
		oled_pos(6,40);		
		oled_printf("Back to menu");
	}
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
		oled_printf("Back to settnigs");

			



	}	

	
}