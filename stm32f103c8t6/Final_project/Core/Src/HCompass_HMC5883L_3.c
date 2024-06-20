/*
 * HCompass_GY_271.c
 *
 *  Created on: Jan 6, 2024
 *      Author: Omar
 */


/**************************************/
/*				Includes			  */
/**************************************/

#include <Config.h>
#include <HCompass_HMC5883L_3.h>
#include <math.h>

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- Compass_Init
 * @brief		- Initializes the Compass
 * @retval		- ErrorState: returns HAL_OK if the compass is connected properly
 *
 * Note			-
 */

compass_S compass;

HAL_StatusTypeDef HCompass_Init()
{
	HAL_StatusTypeDef ErrorState;
	uint8_t dataBuffer[3];
	uint8_t CheckRegA, CheckRegB, CheckRegC;

	/* Detect the Compass first */
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

	/* Checking for the right values in the compass in identification registers */
	if(CheckRegA == 'H' && CheckRegB == '4' && CheckRegC == '3')
	{
		/* Connected successfully */
		ErrorState = HAL_OK;

		/* Access the Mode Register to set the Compass mode to Continuous measurement mode */
		HAL_I2C_Mem_Write(
				&I2C_BUS,
				COMPASS_SLAVE_ADDRESS,
				COMPASS_MODE_REGISTER_ADDRESS, 1,
				(uint8_t*)0x00, 1,
				HAL_MAX_DELAY
		);
	}

	return ErrorState;
}

/**========================================================
 * @Fn			- HCompass_ReadAxis
 * @brief		- Reads the positions of the three Axis X, Y, Z
 * @param[out]	- X: pointer that points to the position of the X Axis
 * @param[out]	- Y: pointer that points to the position of the Y Axis
 * @param[out]	- Z: pointer that points to the position of the Z Axis
 * @retval		- ErrorState: Returns HAL_OK if the Readings was received successfully
 * Note			- If the readings were not received successfully, X, Y, Z will keep their old values
 */
HAL_StatusTypeDef HCompass_ReadAxis()
{
	uint8_t dataBuffer[6] = {0}; // The ADC Reading of the 3 Axis in 6 Bytes (Every Axis in 2 Bytes)
	HAL_StatusTypeDef ErrorState; // acknowledge from the Compass' I2C Address

	/* Accessing the Axis Registers from the Compass starting with the X Axis as an offset */
	/* Getting the 6 Bytes of the ADC Reading for the 3 Axis */
	ErrorState = HAL_I2C_Mem_Read(
			&I2C_BUS,
			COMPASS_SLAVE_ADDRESS,
			COMPASS_X_MSB_ADDRESS, 1,
			dataBuffer, 6,
			HAL_MAX_DELAY
	);

	/* Checking if the reading was received successfully */
	if(ErrorState == HAL_OK)
	{
		/* Combining the 2 Bytes of X Axis into one variable */
		compass.X = ((uint16_t)dataBuffer[0] << 8) | dataBuffer[1];

		/* Combining the 2 Bytes of Y Axis into one variable */
		compass.Z = ((uint16_t)dataBuffer[2] << 8) | dataBuffer[3];

		/* Combining the 2 Bytes of Z Axis into one variable */
		compass.Y = ((uint16_t)dataBuffer[4] << 8) | dataBuffer[5];

		calculate_compass_direction(compass.Y ,compass.X );
	}

	return ErrorState;
}

void calculate_compass_direction(int16_t x, int16_t y) {
	double angle = atan2(y, x) * RAD_TO_DEG;
    if (angle < 0) {
    	compass.direction = 360.0 + angle;
    } else {
    	compass.direction = angle;
    }

}
