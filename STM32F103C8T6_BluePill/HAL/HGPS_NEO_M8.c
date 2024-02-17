/*
 * HGPS_NEO_M8.c
 *
 *  Created on: Jan 12, 2024
 *      Author: Omar
 */


/**************************************/
/*				Includes			  */
/**************************************/

#include <Config.h>

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/


uint8_t* HGPS_GetInformations()
{
	uint8_t dataBuffer[60];
	HAL_UART_Receive(&GPS_UART, dataBuffer, 60, HAL_MAX_DELAY);

	return dataBuffer;
}
