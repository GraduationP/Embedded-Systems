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

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- HCompass_ReadAxis
 * @brief		- Reads the positions of the three Axis X, Y, Z
 * @param[out]	- X: pointer that points to the position of the X Axis
 * @param[out]	- Y: pointer that points to the position of the Y Axis
 * @param[out]	- Z: pointer that points to the position of the Z Axis
 * @retval		- ErrorState: Returns HAL_OK if the Readings was received successfully
 * Note			- If the readings were not received successfully, X, Y, Z will keep their old values
 */
HAL_StatusTypeDef HCompass_ReadAxis(uint16_t* X, uint16_t* Y, uint16_t* Z)
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
		*X = (((uint16_t)dataBuffer[0]&(~0xF8)) << 8) | dataBuffer[1];

		/* Combining the 2 Bytes of Y Axis into one variable */
		*Y = (((uint16_t)dataBuffer[2]&(~0xF8)) << 8) | dataBuffer[3];

		/* Combining the 2 Bytes of Z Axis into one variable */
		*Z = (((uint16_t)dataBuffer[4]&(~0xF8)) << 8) | dataBuffer[5];
	}

	return ErrorState;
}

