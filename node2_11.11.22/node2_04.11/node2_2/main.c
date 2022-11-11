#include "sam.h"
#include "printf-stdarg.h"
#include "uart.h"
#include "can_controller.h"
#include "pwm_driver.h"
#include "adc_driver.h"
#include "dac_driver.h"
#include "motor_driver.h"
#include "delay.h"
//#include "types.h"

CAN_MESSAGE message;
int main(  )
{
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS;	// Watchdog disabled
	// Init the systick
	//SysTick_Config(84);
	configure_uart();
	can_setup();
	pwm_init();
	adc_init();
	dac_init();
	motor_box_init();
	
	printf("\r\nInit complete\n\r");

	//for (int i = 0; i < 5; i++){
		//printf("vent ett sekund\n\r");
		//delay_ms(1000);
	//}
	
	while(1){
	//printf("%d\n\r",message.data[2]);
	dac_write(message.data[2]);
	//motor_dir(message.data[2]);
	printf("%d\n\r",message.data[2]);
	}
}


// moved interrupt handle to main to be able to read message.() globally
void CAN0_Handler( void )
{
	//if(DEBUG_INTERRUPT)printf("CAN0 interrupt\n\r");
	char can_sr = CAN0->CAN_SR; 
	
	//RX interrupt
	if(can_sr & (CAN_SR_MB1 | CAN_SR_MB2) )//Only mailbox 1 and 2 specified for receiving
	{
	
		if(can_sr & CAN_SR_MB1)  //Mailbox 1 event
		{
			can_receive(&message, 1);
			//printf("\n\r################### NEW EVENT BUF 1 #####################\n\r");
			//printf("Got message with id: %d\t\n\r", message.id);
			//printf("Got message with length: %d\t\n\r", message.data_length);
			//printf("Data Y:\t%d\n\r",message.data[0]);
			//printf("Data X:\t%d\n\r",message.data[1]);
			//printf("Data Right slider:\t%d\n\r",message.data[2]);
			//printf("Data Left slider:\t%d\n\r",message.data[3]);
			//printf("Joy button:\t%d\n\r",message.data[4]);
			//printf("Right button:\t%d\n\r",message.data[5]);
			//printf("Left button:\t%d\n\r",message.data[6]);
		}
		else if(can_sr & CAN_SR_MB2) //Mailbox 2 event
		
		{
			can_receive(&message, 2);
		}
		else
		{
			printf("CAN0 message arrived in non-used mailbox\n\r");
		}

	}
	
	if(can_sr & CAN_SR_MB0)
	{
		//if(DEBUG_INTERRUPT) printf("CAN0 MB0 ready to send \n\r");
		
	//Disable interrupt
		CAN0->CAN_IDR = CAN_IER_MB0;

	}

	if(can_sr & CAN_SR_ERRP)
	{
		//if(DEBUG_INTERRUPT)printf("CAN0 ERRP error\n\r");

	}
	if(can_sr & CAN_SR_TOVF)
	{
		//if(DEBUG_INTERRUPT)printf("CAN0 timer overflow\n\r");

	}
	
	NVIC_ClearPendingIRQ(ID_CAN0);
	//sei();*/
}


//MATCH TQ, bør og være samme verdier i phase seg og prop seg

// to print numberz printf("%d",1);