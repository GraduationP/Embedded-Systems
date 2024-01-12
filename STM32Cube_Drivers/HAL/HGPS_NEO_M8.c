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
#include <stm32f1xx_hal_uart.h>
#include <stm32f1xx_ll_usart.h>

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/


uint8_t* HGPS_GetInformations()
{
	uint8_t* dataBuffer = 0x00;
	HAL_UART_Receive(&GPS_UART, dataBuffer, 40, HAL_MAX_DELAY);
	return dataBuffer;
}
