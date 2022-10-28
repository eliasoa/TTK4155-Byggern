#include "sam.h"

#include "printf-stdarg.h"
#include "uart.h"
#include "can_controller.h"
#include "can_interrupt.h"

int main(  )
{
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS;	// Watchdog disabled
	configure_uart();
	can_setup();
	
	CAN_MESSAGE message;
	//message.id = 5;
	//message.data[0] = 'A';
	//message.data[1] = 'B';
	//message.data[2] = 'C';
	//message.data[3] = 'D';
	//message.data[4] = 'E';
	//message.data[5] = 'F';
	//message.data[6] = 'G';
	//message.data[7] = 'H';
	//message.data_length = 8;
	

	
	
	while(1){
	//for (int i = 0; i < 10000000; i++){
		//int v = i;
		//};
	//can_receive(&message,0);
	
	}
	printf("\n\r");

}








//MATCH TQ, bør og være samme verdier i phase seg og prop seg

// to print numberz printf("%d",1);