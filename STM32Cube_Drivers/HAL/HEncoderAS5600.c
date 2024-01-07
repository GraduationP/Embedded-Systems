/*
 * HEncoderAS5600.c
 *
 *  Created on: Jan 6, 2024
 *      Author: Omar
 */


/**************************************/
/*				Includes			  */
/**************************************/

#include <Config.h>
#include <HEncoderAS5600.h>

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- HEncoder_ReadAngle
 * @brief		- Entering blocking mode until the sensor detects a magnet and it's in the right position
 * @retval		- None
 * Note			- Angle output from (0 to 3600)
 */
void HEncoder_CheckStatus()
{
	HAL_StatusTypeDef ret; // acknowledge from the Encoder's I2C Address
	uint8_t StatusError;
	/* Accessing the Status Register from the Encoder */
	ret = HAL_I2C_Master_Transmit(&I2C_BUS, ENCODER_SLAVE_ADDRESS, ENCODER_STATUS_ADDRESS, 1, HAL_MAX_DELAY);

	/* Checking acknowledge from the Encoder's I2C Address */
	if(ret == HAL_OK)
	{
		/* Getting the Status of the encoder readings */
		ret = HAL_I2C_Master_Receive(&I2C_BUS, ENCODER_SLAVE_ADDRESS, &StatusError, 1, HAL_MAX_DELAY);

		/* Entering blocking mode until the sensor detects a magnet and it's in the right position */
		while(ret == HAL_OK && StatusError != 0x20)
		{
			/* Keep reading from the status register */
			ret = HAL_I2C_Master_Receive(&I2C_BUS, ENCODER_SLAVE_ADDRESS, &StatusError, 1, HAL_MAX_DELAY);
		}
	}
}

/**========================================================
 * @Fn			- HEncoder_ReadAngle
 * @brief		- Reads using I2C the angle of the magnetic encoder read by the ADC in the sensor
 * @param[out]	- u16EncoderReading: uint16 pointer that stores the angle
 * @retval		- None
 * Note			- Angle output from (0 to 360)
 */
void HEncoder_ReadAngle(uint16_t* u16EncoderReading)
{
	uint8_t dataBuffer[2]; // The ADC Reading of the angle in 2 Bytes
	HAL_StatusTypeDef ret; // acknowledge from the Encoder's I2C Address

	/* Accessing the Angle Register from the Encoder */
	ret = HAL_I2C_Master_Transmit(&I2C_BUS, ENCODER_SLAVE_ADDRESS, ENCODER_RAW_ANGLE_ADDRESS, 1, HAL_MAX_DELAY);

	/* Checking acknowledge from the Encoder's I2C Address */
	if(ret == HAL_OK)
	{
		/* Getting the 2 Bytes of the ADC Reading from the Angle Register */
		ret = HAL_I2C_Master_Receive(&I2C_BUS, ENCODER_SLAVE_ADDRESS, dataBuffer, 2, HAL_MAX_DELAY);

		/* Checking if the reading was received successfully */
		if(ret == HAL_OK)
		{
			/* Combining the 2 Bytes into one variable */
			*u16EncoderReading = (uint16_t)dataBuffer[0] << 8 | dataBuffer[1];

			/* Converting the ADC value to degrees from 0 to 360 */
			*u16EncoderReading = (uint16_t)(*u16EncoderReading *(360.0/4096));
		}
	}
}




