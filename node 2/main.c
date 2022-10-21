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
	printf("letsgooo");
	

	while(1){
	
	}

}

//MATCH TQ, bør og være samme verdier i phase seg og prop seg

// to print numberz printf("%d",1);