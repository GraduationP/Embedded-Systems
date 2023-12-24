/*
 * Servo.c
 *
 *  Created on: Dec 23, 2023
 *      Author: Omar
 */

/**************************************/
/*				Includes			  */
/**************************************/
#include <stm32f1xx_ll_tim.h>
#include <stm32f1xx_hal_gpio.h>
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
void HServo_Init(TimerConf_TypeDef *Servo_TimerConf)
{
	HAL_TIM_PWM_Start(Servo_TimerConf->htim, Servo_TimerConf->Channel);
}


/**========================================================
 * @Fn			- HServo_writePosition
 * @brief		- Writes the position of the servo
 * @param[in]	- Servo_TimerConfig: Contains the desired timer and channel informations
 * @param[in]	- u8ServoPosition: The desired position of the servo. must be from 0 to 180
 * @retval		- None
 * Note			-
 */
void HServo_writePosition(TimerConf_TypeDef *Servo_TimerConf, uint8_t u8ServoPosition)
{
	/* Mapping position to microseconds */
	uint16_t OnTime_us = map(u8ServoPosition, 0, 180, 500, 2500);

	/* Writing the position of the servo as PWM signal */
	PWM_ModifyOnTime(Servo_TimerConf, OnTime_us);
}


/**========================================================
 * @Fn			- HServo_writeMicroseconds
 * @brief		- Writes the OnTime Pulse of PWM to the servo motor in Microseconds
 * @param[in]	- Servo_TimerConfig: Contains the desired timer and channel informations
 * @param[in]	- u16Value: PWM OnTime in Microseconds. Muse be from 500 to 2500
 * Note			-
 */
void HServo_writeMicroseconds(TimerConf_TypeDef *Servo_TimerConf, uint32_t u32Value)
{
	PWM_ModifyOnTime(Servo_TimerConf, u32Value);
}


/**========================================================
 * @Fn			- HServo_DeInit
 * @brief		- Detaching the servo pin (Stopping PWM Signal)
 * @param[in]	- Servo_TimerConfig: Timer and Channel to stop its' PWM
 * @retval		- None
 * Note			-
 */
void HServo_DeInit(TimerConf_TypeDef *Servo_TimerConf)
{
	/* Stopping PWM Signal */
	//	HAL_TIM_PWM_Stop(
	//			Servo_TimerConfig->htim,
	//			Servo_TimerConfig->Channel
	//	);
}
