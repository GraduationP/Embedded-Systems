/*
 * PID.c
 *
 *  Created on: Dec 24, 2023
 *      Author: Omar
 */


/**************************************/
/*				Includes			  */
/**************************************/
#include <PID.h>

/**************************************/
/*			Generic Functions		  */
/**************************************/


/**************************************/
/*			Generic Variables		  */
/**************************************/

/* DC Motor Variables */
uint16_t	P_DCMotor;
uint16_t	I_DCMotor 					= 0;
uint16_t	D_DCMotor;
uint16_t	DC_Motor_Previous_Error 	= 0;

/* Servo Motor Variables */
uint16_t	P_Servo;
uint16_t	I_Servo						= 0;
uint16_t	D_Servo;
uint16_t	Servo_Previous_Error		= 0;

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- PID_DC_Motor_Compute
 * @brief		- Computing the Response value from PID for DC Motor
 * @param[in]	- PID_DC_Motor_Config: Contains the PID informations for the DC Motor
 * @retval		- None
 * Note			-
 */
void PID_DC_Motor_Compute(PID_Config_t* PID_DC_Motor_Config)
{
	uint16_t u16_LocalPID_Response;

	/* Proportional */
	P_DCMotor = *(PID_DC_Motor_Config->Error);

	/* Integral */
	I_DCMotor += *(PID_DC_Motor_Config->Error);

	/* Derivative */
	D_DCMotor = *(PID_DC_Motor_Config->Error) - DC_Motor_Previous_Error;

	/* Updating Previous error */
	DC_Motor_Previous_Error = *(PID_DC_Motor_Config->Error);

	/* Summing it all together in Response */
	u16_LocalPID_Response = P_DCMotor * PID_DC_Motor_Config->Kp
			+ I_DCMotor * PID_DC_Motor_Config->Ki
			+ D_DCMotor * PID_DC_Motor_Config->Kd;

	/* Constraining the Output in the limits */
	if(u16_LocalPID_Response > PID_DC_Motor_Config->OutputMaxLimit)
	{
		u16_LocalPID_Response = PID_DC_Motor_Config->OutputMaxLimit;
	}
	else if(u16_LocalPID_Response < PID_DC_Motor_Config->OutputMinLimit)
	{
		u16_LocalPID_Response = PID_DC_Motor_Config->OutputMinLimit;
	}

	/* The final result */
	*PID_DC_Motor_Config->Response = u16_LocalPID_Response;
}



/**========================================================
 * @Fn			- PID_Servo_Compute
 * @brief		- Computing the Response value from PID for Servo Motor
 * @param[in]	- PID_Servo_Config: Contains the PID informations for the Servo Motor
 * @retval		- None
 * Note			-
 */
void PID_Servo_Compute(PID_Config_t* PID_Servo_Config)
{
	uint16_t u16_LocalPID_Response;

	/* Proportional */
	P_Servo = *(PID_Servo_Config->Error);

	/* Integral */
	I_Servo += *(PID_Servo_Config->Error);

	/* Derivative */
	D_Servo = *(PID_Servo_Config->Error) - Servo_Previous_Error;

	/* Updating Previous error */
	Servo_Previous_Error = *(PID_Servo_Config->Error);

	/* Summing it all together in Response */
	u16_LocalPID_Response = P_Servo * PID_Servo_Config->Kp
			+ I_Servo * PID_Servo_Config->Ki
			+ D_Servo * PID_Servo_Config->Kd;

	/* Constraining the Output in the limits */
	if(u16_LocalPID_Response > PID_Servo_Config->OutputMaxLimit)
	{
		u16_LocalPID_Response = PID_Servo_Config->OutputMaxLimit;
	}
	else if(u16_LocalPID_Response < PID_Servo_Config->OutputMinLimit)
	{
		u16_LocalPID_Response = PID_Servo_Config->OutputMinLimit;
	}

	/* The final result */
	*PID_Servo_Config->Response = u16_LocalPID_Response;
}
