/*
 * PID.h
 *
 *  Created on: Dec 24, 2023
 *      Author: Omar
 */

#ifndef INC_PID_H_
#define INC_PID_H_


/**************************************/
/*				Includes		  	  */
/**************************************/

#include <stdint.h>

/**************************************/
/*			 PID Structures	       	  */
/**************************************/

typedef struct{
	uint16_t*	Setpoint;			// Desired Target for computing the error accordingly
									// pointer to make it changeable anywhere in the code

	uint16_t*	Error;				// The feedback from a sensor
									// pointer to make it changeable anywhere in the code

	uint16_t*	Response;			// The output from the PID computation
									// pointer to make it changeable anywhere in the code

	uint8_t		Kp;					// Proportional constant
	uint8_t		Ki;					// Integral constant
	uint8_t		Kd;					// Derivative constant

	uint16_t	OutputMinLimit;		// Minimum output vale
	uint16_t	OutputMaxLimit;		// Maximum output value
}PID_Config_t;

/**************************************/
/*		 	Macros References 	  	  */
/**************************************/


/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/

/* Computing the Response value from PID for DC Motor */
void PID_DC_Motor_Compute(PID_Config_t* PID_DC_Motor_Config);

/* Computing the Response value from PID for Servo Motor */
void PID_Servo_Compute(PID_Config_t* PID_Servo_Config);

#endif /* INC_PID_H_ */
