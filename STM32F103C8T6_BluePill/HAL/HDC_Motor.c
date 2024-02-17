/*
 * DC_Motor.c
 *
 *  Created on: Dec 15, 2023
 *      Author: Omar
 */

/**************************************/
/*				Includes			  */
/**************************************/
#include <stm32f1xx_ll_tim.h>
#include <stm32f1xx_hal_gpio.h>
#include <HDC_Motor.h>
#include <Config.h>
/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- HDC_Motor_Timer_Init
 * @brief		- Initializes the DC Motor PWM Pin
 */
void HDC_Motor_Timer_Init()
{
	/* Starts the DC Motor SpeedPin Timer PWM (EN) */
	HAL_TIM_PWM_Start(&DC_MOTOR_TIMER, DC_MOTOR_CHANNEL);
}


/**========================================================
 * @Fn			- HDC_Motor_Direction
 * @brief		- Controls the direction of the DC Motor
 * @param[in]	- u8Direction: The direction of the DC Motor. Must be set as: DC_MOTOR_BACKWARD,
 * 																			  DC_MOTOR_FORWARD,
 * 																			  DC_MOTOR_STOP,
 * 																			  DC_MOTOR_BRAKE
 * @retval		- None
 * Note			-
 */
void HDC_Motor_Direction(uint8_t u8Direction)
{
	/* Writing Direction of the first pin */
	uint8_t Local_u8Direction1  = u8Direction %2;	// First bit of the variable
	HAL_GPIO_WritePin(DC_MOTOR_PIN1_GPIO, DC_MOTOR_PIN1, Local_u8Direction1);

	/* Writing Direction of the second pin */
	uint8_t Local_u8Direction2  = u8Direction >> 1;	// Second bit of the variable
	HAL_GPIO_WritePin(DC_MOTOR_PIN2_GPIO, DC_MOTOR_PIN2, Local_u8Direction2);
}


/**========================================================
 * @Fn			- HDC_Motor_Speed
 * @brief		- Sets the speed of the DC Motor using a PWM signal
 * @param[in]	- u32Speed: the speed of the DC Motor in PWM. Values between (0):(255)
 * @retval		- None
 * Note			-
 */
void HDC_Motor_Speed(uint8_t u8Speed)
{
	__HAL_TIM_SET_COMPARE(&DC_MOTOR_TIMER, DC_MOTOR_CHANNEL, (uint16_t)u8Speed);
}

