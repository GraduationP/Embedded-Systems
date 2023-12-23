/*
 * Servo.c
 *
 *  Created on: Dec 23, 2023
 *      Author: Omar
 */

/**************************************/
/*				Includes			  */
/**************************************/

#include <HServo_Motor.h>



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
 * @Fn			- HServo_Init
 * @brief		- Initializes the desired Servo Motor pin
 * @param[in]	- Servo_TimerConfig: Contains the desired timer and channel informations
 * @retval		- None
 * Note			-
 */
void HServo_Init(TimerPin_TypeDef* Servo_TimerConfig)
{

}


/**========================================================
 * @Fn			- HServo_writePosition
 * @brief		- Writes the position of the servo
 * @param[in]	- Servo_TimerConfig: Contains the desired timer and channel informations
 * @param[in]	- u8ServoPosition: The desired position of the servo. must be from 0 to 180
 * @retval		- None
 * Note			-
 */
void HServo_writePosition(TimerPin_TypeDef* Servo_TimerConfig, uint8_t u8ServoPosition)
{
	/* Mapping position to microseconds */
	uint16_t OnTime_us = map(u8ServoPosition, 0, 180, 500, 2500);

	/* Preparing Timer mode and PWM Configuration */
	TIM_OC_InitTypeDef sConfigOC = {0};

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = OnTime_us;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	/* Stopping previous PWM Signal */
	HAL_TIM_PWM_Stop(
			Servo_TimerConfig->htim,
			Servo_TimerConfig->Channel
	);

	/* Configuring Timerx Channelx to modify the speed */
	HAL_TIM_PWM_ConfigChannel(
			Servo_TimerConfig->htim,
			&sConfigOC,
			Servo_TimerConfig->Channel
	);

	/* Starting the desired PWM signal */
	HAL_TIM_PWM_Start(
			Servo_TimerConfig->htim,
			Servo_TimerConfig->Channel
	);
}


/**========================================================
 * @Fn			- HServo_writeMicroseconds
 * @brief		- Writes the OnTime Pulse of PWM to the servo motor in Microseconds
 * @param[in]	- Servo_TimerConfig: Contains the desired timer and channel informations
 * @param[in]	- u16Value: PWM OnTime in Microseconds. Muse be from 500 to 2500
 * Note			-
 */
void HServo_writeMicroseconds(TimerPin_TypeDef* Servo_TimerConfig, uint16_t u16Value)
{
	/* Preparing Timer mode and PWM Configuration */
	TIM_OC_InitTypeDef sConfigOC = {0};

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = u16Value;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	/* Stopping previous PWM Signal */
	HAL_TIM_PWM_Stop(
			Servo_TimerConfig->htim,
			Servo_TimerConfig->Channel
	);

	/* Configuring Timerx Channelx to modify the Servo Position */
	HAL_TIM_PWM_ConfigChannel(
			Servo_TimerConfig->htim,
			&sConfigOC,
			Servo_TimerConfig->Channel
	);

	/* Starting the desired PWM signal */
	HAL_TIM_PWM_Start(
			Servo_TimerConfig->htim,
			Servo_TimerConfig->Channel
	);
}


/**========================================================
 * @Fn			- HServo_DeInit
 * @brief		- Detaching the servo pin (Stopping PWM Signal)
 * @param[in]	- Servo_TimerConfig: Timer and Channel to stop its' PWM
 * @retval		- None
 * Note			-
 */
void HServo_DeInit(TimerPin_TypeDef* Servo_TimerConfig)
{
	/* Stopping PWM Signal */
	HAL_TIM_PWM_Stop(
			Servo_TimerConfig->htim,
			Servo_TimerConfig->Channel
	);
}
