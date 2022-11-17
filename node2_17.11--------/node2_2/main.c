#include "sam.h"
#include "printf-stdarg.h"
#include "uart.h"
#include "can_controller.h"
#include "pwm_driver.h"
#include "adc_driver.h"
#include "dac_driver.h"
#include "motor_driver.h"
#include "delay.h"
#include "PID.h"
#include "solenoid.h"


#include <stdio.h>
#include <stdlib.h>

int16_t pre_slider_value;

CAN_MESSAGE message;

int main( void ){
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS;	// Watchdog disabled
	// Init the systick
	SysTick_Config(84);
	configure_uart();
	can_setup();
	pwm_init();
	adc_init();
	dac_init();
	motor_box_init();
	solenoid_init();
	printf("\r\nInit complete\n\r");
	uint32_t prev_time = millis();
	uint16_t sampling_time = 10000;
	uint16_t game_over = 0;							// 1 if game over
	
	while(1){
		if (message.data[7] == 1)
		{
			if (millis() >= prev_time + sampling_time){
				servo_get_pos(message.data[1]);
				pos_controller(encoder(),message.data[3]);
				solenoid_trigger(message.data[4]);
				prev_time = millis();
			}
			//game_over = 0;
			//uint16_t score_is = ir_counter(adc_read());
			////printf("Trigger game:\t%d\n\r",message.data[7]);
			//printf("Score:\t%d\n\r",score_is);
			//if (game_over = 1)
			//{
				//can_send( , );
			//}
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
			//printf("Data Left slider:\t%d\n\r",message.data[2]);
			//printf("Data Right slider:\t%d\n\r",message.data[3]);
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

uint8_t threshold_value = 25;

void pos_controller(int16_t encoder_value, uint8_t slider_value){

	if (abs(slider_value-pre_slider_value) < threshold_value)
	{
		slider_value=pre_slider_value;
	}

	int16_t desired_pos = map(slider_value,0,255,0,2810);
	int16_t u = pid_controller(desired_pos, encoder_value);
	motor_dir(u);
	//printf("\n\r####################\n\r");
	//printf("Desired position is: %d\t\n\r",desired_pos);
	//printf("Current position is: %d\t\n\r",encoder_value);
	//printf("               u is: %d\t\n\r",u);
	pre_slider_value = slider_value;
	//printf("Slider value: %d\t\n\r",slider_value);
}

void solenoid_trigger(int button)
{
	while ( button == 0)
	{
		PIOB -> PIO_CODR = PIO_PB26;			//Set high
		motor_dir(0);
		button = message.data[4];
	}
	PIOB ->PIO_SODR = PIO_PB26;
}



//printf("%d\n\r",message.data[2]);
	//dac_write(message.data[2]);
	//motor_dir(message.data[0]);
	//printf("%d\n\r",map(message.data[2],0,255,0,2810));
	//delay_us(10000);
	//printf("%d\n\r",encoder());
	//printf("%d\n\r",message.data[3]);
	//motor_dir(message.data[1]);
	//printf("%d\n\r",message.data[4]);
	//printf("Starter å vente\n\r");
	//delay_ms(1000);
	//printf("Har ventet i et sekund\n\r");
	