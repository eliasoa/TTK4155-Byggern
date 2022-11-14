#include "PID.h"

// Only PI control is implemented


uint16_t error[2]={0,0};			// Current and previous error
int16_t process_value[2]={0,0};	// Current and previous processvalue
int16_t i_term[2]={0,0};          // Current and previous integral term

int16_t pid_controller(int16_t setpoint, int16_t processvalue){


	int16_t p_term,u;
	//Init parameters
	
	//Proportional gain
	int16_t Kp_factor = 1;
	//Integral gain
	int16_t Ki_factor = 1;
	

	//Setting processvalue
	process_value[0] = processvalue;
	
	// Compute error
	error[0] = setpoint - process_value[0];
	
	// Compute proportional term
	p_term = Kp_factor * error[0];
	
	
	
	//Compute integral term
	int16_t sumerror_limit_max = 100;
	int16_t sumerror_limit_min = 0;	
	
	int16_t integral_limit_max = 100;
	int16_t integral_limit_min = 0;	
	// Integral limiter
	if (error[1] > sumerror_limit_max)
	{
		error[1] = sumerror_limit_max;
		i_term[0] = integral_limit_max;		
	}
	else if (error[1] < sumerror_limit_min)
	{
		error[1] = sumerror_limit_min;
		i_term[0] = integral_limit_min;
	}
	else
	{
		i_term[0] = i_term[1] + Ki_factor*error[1];
	}
	
	//Total output
	u = p_term + i_term[0];
	
	//Update values
	error[1] += error[0];
	process_value[1] = process_value[0];
	i_term[1] = i_term[0];
	
	//printf("e:%d\t\n\r",error[0]);
	//printf("e sum:%d\t\n\r",error[1]);
	//printf("P:%d\t\n\r",p_term);
	//printf("i:%d\t\n\r",i_term[0]);
	//printf("u:%d\t\n\r",u);
	return u;
}