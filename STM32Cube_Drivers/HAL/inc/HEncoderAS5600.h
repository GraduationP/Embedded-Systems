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

#define ENCODER_SLAVE_ADDRESS		0x36<<1		// First bit is the R/W bit
#define ENCODER_ANGLE_ADDRESS		0x0F
#define ENCODER_STATUS_REG			0x08

/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/

void HEncoder_ReadRawAngle();

#endif /* INC_HENCODERAS5600_H_ */
