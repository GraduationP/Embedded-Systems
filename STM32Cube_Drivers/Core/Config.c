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
#include <HEncoderAS5600.h>
#include <HCompass_HMC5883L_3.h>

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

void Encoder_Start()
{
	/* Stores the initial encoder reading to calculate number of turns */

}

void Compass_Start()
{
	HAL_StatusTypeDef ret;

	/* Accessing the Mode Register in the Compass */
	ret = HAL_I2C_Master_Transmit(&I2C_BUS, COMPASS_SLAVE_ADDRESS, (uint8_t*)0x02, 1, HAL_MAX_DELAY);

	/* Checking acknowledge from the Compass' I2C Address */
	if(ret == HAL_OK)
	{
		/* Set the Compass mode to Continuous measurement mode */
		HAL_I2C_Master_Transmit(&I2C_BUS, COMPASS_SLAVE_ADDRESS, (uint8_t*)0x00, 1, HAL_MAX_DELAY);
	}
}

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- Hardware_Start
 * @brief		- Starts all of the Hardware Components
 * @retval		- None
 * Note			- This function only starts the Components to operate.
 * 				  The STM32Cube does all the initialization needed
 */
void Hardware_Start()
{
	Servo_Timer_Start();
	DC_Motor_Timer_Start();
	Encoder_Start();
	Compass_Start();
}
