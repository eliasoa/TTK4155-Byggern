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
	
	CAN_MESSAGE test_message;
	test_message.id = 1;
	test_message.data[0] = 'A';
	test_message.data[1] = 'A';
	test_message.data[2] = 'A';
	test_message.data[3] = 'A';
	test_message.data[4] = 'A';
	test_message.data[5] = 'A';
	test_message.data[6] = 'A';
	test_message.data[7] = 'A';
	test_message.data_length = 8;
	

	
	
	while(1){
	printf("Sender melding: ");
	printf("\r",test_message.data);
	
	can_send( &test_message, 0 );
	}

}








//MATCH TQ, bør og være samme verdier i phase seg og prop seg

// to print numberz printf("%d",1);