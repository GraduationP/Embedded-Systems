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

#define COMPASS_SLAVE_ADDRESS				0x1E << 1
#define COMPASS_MODE_REGISTER_ADDRESS		0x02
#define COMPASS_X_MSB_ADDRESS				0x03
#define COMPASS_IDENTIFICATION_ADDRESS		0x0A


#define RAD_TO_DEG 180.0 / M_PI
/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/
typedef struct
{
	int16_t X;
	int16_t Y;
	int16_t Z;
	uint8_t direction;
}compass_S;

extern compass_S compass;

/* Initializes the Compass */
HAL_StatusTypeDef HCompass_Init();

/* Reads the positions of the three Axis X, Y, Z */
HAL_StatusTypeDef HCompass_ReadAxis();

void calculate_compass_direction(int16_t x, int16_t y);

#endif /* INC_HCOMPASS_HMC5883L_3_H_ */
