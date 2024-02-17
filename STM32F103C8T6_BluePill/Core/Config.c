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
#include <HDC_Motor.h>
#include <HServo_Motor.h>
#include <HnRF24L01.h>
#include <HGPS_NEO_M8.h>
#include <HEncoderAS5600.h>
#include <HCompass_HMC5883L_3.h>

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- Hardware_Start
 * @brief		- Initializes all of the Hardware Components
 * @retval		- None
 * Note			-
 */
void Hardware_Init()
{
	HServo_Timer_Init();
	HDC_Motor_Timer_Init();
//	HEncoder_Init();
//	HCompass_Init();
//	HnRF24_Init();
}
