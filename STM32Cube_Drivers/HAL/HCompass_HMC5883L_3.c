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
 * @param[out]	- X: The position of the X Axis
 * @param[out]	- Y: The position of the Y Axis
 * @param[out]	- Z: The position of the Z Axis
 * @retval		- None
 * Note			-
 */
void HCompass_ReadAxis(uint16_t* X, uint16_t* Y, uint16_t* Z)
{
	uint8_t dataBuffer[6]; // The ADC Reading of the 3 Axis in 6 Bytes (Every Axis in 2 Bytes)
	HAL_StatusTypeDef ret; // acknowledge from the Compass' I2C Address

	/* Accessing the Axis Registers from the Compass starting with the X Axis as an offset */
	ret = HAL_I2C_Master_Transmit(&I2C_BUS, COMPASS_SLAVE_ADDRESS, COMPASS_X_MSB_ADDRESS, 1, HAL_MAX_DELAY);

	/* Checking acknowledge from the Compass' I2C Address */
	if(ret == HAL_OK)
	{
		/* Getting the 6 Bytes of the ADC Reading for the 3 Axis */
		ret = HAL_I2C_Master_Receive(&I2C_BUS, COMPASS_SLAVE_ADDRESS, dataBuffer, 6, HAL_MAX_DELAY);

		/* Checking if the reading was received successfully */
		if(ret == HAL_OK)
		{
			/* Combining the 2 Bytes of X Axis into one variable */
			*X = (uint16_t)dataBuffer[0] << 8 | dataBuffer[1];

			/* Combining the 2 Bytes of Y Axis into one variable */
			*Y = (uint16_t)dataBuffer[2] << 8 | dataBuffer[3];

			/* Combining the 2 Bytes of Z Axis into one variable */
			*Z = (uint16_t)dataBuffer[4] << 8 | dataBuffer[5];
		}
	}
}
