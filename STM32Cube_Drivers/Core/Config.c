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
	HAL_StatusTypeDef ErrorState;

	do{
		ErrorState = HEncoder_CheckStatus();
	}while(ErrorState != HAL_OK);


	/* Stores the initial encoder reading to calculate number of turns */
}

HAL_StatusTypeDef Compass_Start()
{
	HAL_StatusTypeDef ErrorState;
	uint8_t dataBuffer[3];
	uint8_t CheckRegA, CheckRegB, CheckRegC;

	/* Detect the Compass first */
	do{
		/* Checking for the right values in the compass in identification registers */
		ErrorState = HAL_I2C_Mem_Read(
				&I2C_BUS,
				COMPASS_SLAVE_ADDRESS,
				COMPASS_IDENTIFICATION_ADDRESS, 1,
				dataBuffer, 3,
				HAL_MAX_DELAY
		);

		/* Assigning values from Identification Registers A, B, C */
		CheckRegA = dataBuffer[0];
		CheckRegB = dataBuffer[1];
		CheckRegC = dataBuffer[2];
	}while(CheckRegA != 'H' || CheckRegB != '4' || CheckRegC != '3');

	/* Access the Mode Register to set the Compass mode to Continuous measurement mode */
	ErrorState = HAL_I2C_Mem_Write(
			&I2C_BUS,
			COMPASS_SLAVE_ADDRESS,
			COMPASS_MODE_REGISTER_ADDRESS, 1,
			(uint8_t*)0x00, 1,
			HAL_MAX_DELAY
	);

	return ErrorState;
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
