/*
 * Config.c
 *
 *  Created on: Jan 5, 2024
 *      Author: Omar
 */

/**************************************/
/*				Includes			  */
/**************************************/

#include <Config.h>
#include <stm32f1xx_ll_tim.h>

/**************************************/
/*			Generic Functions		  */
/**************************************/

void Servo_Timer_Start()
{
	/* Start the Servo Motor Timer PWM */
	HAL_TIM_PWM_Start(&SERVO_TIMER, SERVO_CHANNEL);
}

void DC_Motor_Timer_Start()
{
	/* Starts the DC Motor SpeedPin Timer PWM (EN) */
	HAL_TIM_PWM_Start(&DC_MOTOR_TIMER, DC_MOTOR_CHANNEL);
}

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- Hardware_Start
 * @brief		- Starts all of the Hardware Components
 * @retval		- None
 * Note			- This function only starts the peripherals.
 * 				  The STM32Cube does all the initialization needed
 */
void Hardware_Start()
{
	Servo_Timer_Start();
	DC_Motor_Timer_Start();
}
