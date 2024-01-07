/*
 * HEncoderAS5600.h
 *
 *  Created on: Jan 6, 2024
 *      Author: Omar
 */

#ifndef INC_HENCODERAS5600_H_
#define INC_HENCODERAS5600_H_


/**************************************/
/*				Includes			  */
/**************************************/

#include <Config.h>

/**************************************/
/*		 	Macros References 	  	  */
/**************************************/

#define ENCODER_SLAVE_ADDRESS		0x36 << 1		// First bit is the R/W bit
#define ENCODER_STATUS_ADDRESS		(uint8_t *)0x0B
#define ENCODER_RAW_ANGLE_ADDRESS	(uint8_t *)0x0C
#define ENCODER_ANGLE_ADDRESS		(uint8_t *)0x0E

/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/

/* In blocking mode until ensuring that the encoder is working */
void HEncoder_CheckStatus();

/* Reads the desired angle from 0 to 3600 */
void HEncoder_ReadAngle(uint16_t* u16EncoderReading);

/* The number of steps according to the initialized angle from the start of the program */
void HEncoder_numOfSteps(uint16_t* u16PositionReading);

#endif /* INC_HENCODERAS5600_H_ */
