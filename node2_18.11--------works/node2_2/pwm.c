#include "sam.h"
#include "pwm_driver.h"
#include "sam.h"

#define CPRD 13125

void pwm_init ( void ){
	
	//enable PWM in PMC
	PMC -> PMC_PCER1 |= PMC_PCER1_PID36;
	// disable PIO on pin 19
	PIOC -> PIO_PDR |= PIO_PDR_P19;
	// B on P19
	PIOC -> PIO_ABSR |= PIO_ABSR_P19;
	
	//  CLKA = MCK/128 = 656250 | invert the signal
	REG_PWM_CMR5 = PWM_CMR_CPRE_MCK_DIV_128| PWM_CMR_CPOL;
	
	//Setting channel period for channel 5, x = 128 -> CPRD = 13125
	// old REG_PWM_CPRD5 = 13125;
	REG_PWM_CPRD5 = 1969;
	
	//Setting channel 5 duty-cycle to middle value
	// old board PWM -> PWM_CH_NUM[5].PWM_CDTY |= 985; //126000/128 // 75 600 to 176 400 (0.9 ms to 2.1 ms)
	PWM -> PWM_CH_NUM[5].PWM_CDTY |= 985; 
	
	//Enabling PWM for channel 5
	PWM -> PWM_ENA |= PWM_ENA_CHID5;
}


void servo_get_pos(uint8_t pos)
{
	int pulse_width;
	//int duty_cycle;	
	// old pulse_width = map(pos, 0, 100, 1378, 590); // 75 600/128 = 590 , 176 400/128 = 1378
	pulse_width = map(pos, 0, 100, 1312, 656); // 75 600/128 = 590 , 176 400/128 = 1378
	REG_PWM_CDTYUPD5 = pulse_width;
	
	//printf("Pulse width:\t%d\n\r",pulse_width);
}

int map(int x, int in_min, int in_max, int out_min, int out_max) {
	// code from https://www.arduino.cc/reference/en/language/functions/math/map/
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}