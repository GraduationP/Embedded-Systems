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
 * @Fn			- HEncoder_CheckStatus
 * @brief		- Checking Encoder Connection before reading the ADC Value
 * @retval		- ErrorState: Returns HAL_OK if the Encoder is detected and in right position
 * Note			- Status values: 0bXXDLHXXX
 * 											D: Magnet Detected,
 * 											L: Magnet Too Weak,
 * 											H: Magnet Too Strong
 * 											Wanted Value: 0x20
 */
HAL_StatusTypeDef HEncoder_CheckStatus()
{
	HAL_StatusTypeDef ErrorState; // acknowledge from the Encoder's I2C Address
	uint8_t EncoderStatus = 0x00;

	/* Checking the Status Register from the encoder */
	ErrorState = HAL_I2C_Mem_Read(
			&I2C_BUS,
			ENCODER_SLAVE_ADDRESS,
			ENCODER_STATUS_ADDRESS, 1,
			&EncoderStatus, 1,
			HAL_MAX_DELAY
	);

	/* Check for desired status */
	if(EncoderStatus == 0x20)
		ErrorState = HAL_OK;

	return ErrorState;
}

/**========================================================
 * @Fn			- HEncoder_ReadAngle
 * @brief		- Reads using I2C the angle of the magnetic encoder read by the ADC in the sensor
 * @param[out]	- u16EncoderReading: 	uint16 pointer that stores the angle
 * @retval		- ErrorState: 			Returns HAL_OK if the angle was received successfully
 * Note			- If the angle was not received successfully, u16EncoderReading won't update it's value
 */
HAL_StatusTypeDef HEncoder_ReadAngle(uint16_t* u16EncoderReading)
{
	uint8_t dataBuffer[2]; // The ADC Reading of the angle in 2 Bytes
	HAL_StatusTypeDef ErrorState; // acknowledge from the Encoder's I2C Address

	/* Accessing the Angle Register from the Encoder */
	/* Getting the 2 Bytes of the ADC Reading from the Angle Register */
	ErrorState = HAL_I2C_Mem_Read(
			&I2C_BUS,
			ENCODER_SLAVE_ADDRESS,
			ENCODER_RAW_ANGLE_ADDRESS, 1,
			dataBuffer, 2,
			HAL_MAX_DELAY);

	/* Checking if the reading was received successfully */
	if(ErrorState == HAL_OK)
	{
		/* Combining the 2 Bytes into one variable */
		*u16EncoderReading = (uint16_t)dataBuffer[0] << 8 | dataBuffer[1];

		/* Converting the ADC value to degrees from 0 to 360 */
		*u16EncoderReading = (uint16_t)(*u16EncoderReading *(360.0/4096));
	}
	return ErrorState;
}


