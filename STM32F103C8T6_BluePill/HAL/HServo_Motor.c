/*
 * Servo.c
 *
 *  Created on: Dec 23, 2023
 *      Author: Omar
 */

/**************************************/
/*				Includes			  */
/**************************************/
#include <Config.h>

/**************************************/
/*			Generic Functions		  */
/**************************************/

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- HServo_Timer_Init
 * @brief		- Initializes the Servo PWM Pin
 * Note			-
 */
void HServo_Timer_Init()
{
	/* Start the Servo Motor Timer PWM */
	HAL_TIM_PWM_Start(&SERVO_TIMER, SERVO_CHANNEL);
}

/**========================================================
 * @Fn			- HServo_writePosition
 * @brief		- Writes the position of the servo
 * @param[in]	- u8ServoPosition: The desired position of the servo. must be from 0 to 180
 * @retval		- None
 * Note			-
 */
void HServo_writePosition(uint8_t u8ServoPosition)
{
	/* Mapping position to microseconds */
	uint16_t OnTime_us = map(u8ServoPosition, 0, 180, 500, 2500);

	/* Writing the position of the servo as PWM signal */
	__HAL_TIM_SET_COMPARE(&SERVO_TIMER, SERVO_CHANNEL, OnTime_us);
}

/**========================================================
 * @Fn			- HServo_writeMicroseconds
 * @brief		- Writes the OnTime Pulse of PWM to the servo motor in Microseconds
 * @param[in]	- u16Value: PWM OnTime in Microseconds. Must be from 500 to 2500
 * Note			-
 */
void HServo_writeMicroseconds(uint16_t u16Value)
{
	__HAL_TIM_SET_COMPARE(&SERVO_TIMER, SERVO_CHANNEL, u16Value);
}

/**========================================================
 * @Fn			- HServo_DeInit
 * @brief		- Detaching the servo pin (Stopping PWM Signal)
 * @retval		- None
 * Note			-
 */
void HServo_DeInit()
{
	/* Stopping PWM Signal */
		HAL_TIM_PWM_Stop(
				&SERVO_TIMER,
				SERVO_CHANNEL
		);
}
