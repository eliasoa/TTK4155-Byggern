#include "PID.h"

// Only PI control is implemented




int16_t pid_controller(int16_t setpoint, int16_t processvalue, int16_t sample){


	int16_t p_term, i_term, sum_error;	
	//Init parameters
	
	//Proportional gain
	int16_t Kp_factor = 0;
	//Integral gain
	int16_t Ki_factor = 0;
	
	//Prop. time
	//int16_t p_time = 0;
	//Integral time
	//int16_t i_time = 0;	

	//Setting processvalue
	process_value[0] = processvalue;
	
	// Compute error
	int16_t error[0] = setpoint - processvalue[0];
	
	// Compute proportional term
	p_term = Kp_factor * error[0];
	
	//Compute integral term
	i_term[0] = i_term[1] + Ki_factor*error[0];
	
	//Total output
	u = p_term + i_term[0];
	
	//Update values
	error[1] = error[0];
	
	i_term[1] = i_term[0]
	
	
}