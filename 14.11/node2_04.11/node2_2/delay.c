#include "sam.h"
#include "delay.h"


static volatile uint32_t DelayTimerTick = 0;

void delay_us(int u){
	SysTick_Config(84);  //Configure the SysTick timer
	DelayTimerTick = u;
	while (DelayTimerTick > 0)
	{//chill
	}
	SysTick->CTRL = 0;
}

//void delay_ms(int u){
	//for (int i = 0; i < u; i++){
		//delay_us(1);
	//}
//}

void SysTick_Handler(){
	DelayTimerTick--;
}
