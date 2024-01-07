/*
 * HCompass_GY_271.h
 *
 *  Created on: Jan 6, 2024
 *      Author: Omar
 */

#ifndef INC_HCOMPASS_HMC5883L_3_H_
#define INC_HCOMPASS_HMC5883L_3_H_

/**************************************/
/*				Includes			  */
/**************************************/


/**************************************/
/*		 	Macros References 	  	  */
/**************************************/

#define COMPASS_SLAVE_ADDRESS		0x1E << 1
#define COMPASS_X_MSB_ADDRESS		(uint8_t*)0x03

/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/

/* Reads the positions of the three Axis X, Y, Z */
void HCompass_ReadAxis(uint16_t* X, uint16_t* Y, uint16_t* Z);

#endif /* INC_HCOMPASS_HMC5883L_3_H_ */
