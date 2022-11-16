#include "sam.h"
#include "delay.h"


static volatile uint32_t DelayTimerTick = 0;
static volatile uint32_t PIDTimerTick = 0;

void delay_us(int u){
	SysTick_Config(84);  //Configure the SysTick timer
	DelayTimerTick = u;
	while (DelayTimerTick > 0)
	{//chill
	}
	SysTick->CTRL = 0;
}

void PID_timer(void){
	SysTick_Config(84);
	PIDTimerTick = 1000;
	
}


void SysTick_Handler(){
	DelayTimerTick--;
	
}
