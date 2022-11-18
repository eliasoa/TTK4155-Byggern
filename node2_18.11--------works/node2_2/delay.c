#include "sam.h"
#include "delay.h"
#include "printf-stdarg.h"


// From IELET1002 lecture week 7
volatile uint32_t ticks = 0;

uint32_t millis( void ){
	return ticks;
}

void SysTick_Handler(void){
	ticks++;
}

void delay_us(uint16_t delay ){
	uint32_t prev_millis = millis();
	while(millis()<=prev_millis+delay){
		//chill bro
		};
}






//static volatile uint32_t DelayTimerTick = 0;
//static volatile uint32_t PIDTimerTick = 0;
//
//void delay_us(int u){
	//SysTick_Config(84);  //Configure the SysTick timer
	//DelayTimerTick = u;
	//while (DelayTimerTick > 0)
	//{//chill
	//}
	//SysTick->CTRL = 0;
//}
//
//void SysTick_Handler(){
	//DelayTimerTick--;
//}