/*
 * DC_Motor.h
 *
 *  Created on: Dec 15, 2023
 *      Author: Omar
 */

#ifndef INC_HDC_MOTOR_H_
#define INC_HDC_MOTOR_H_

/**************************************/
/*		 	Macros References 	  	  */
/**************************************/

// @ref DC_MOTOR_DIRECTION_define
#define DC_MOTOR_DIRECTION_STOP			(uint8_t)0x0
#define DC_MOTOR_DIRECTION_FORWARD		(uint8_t)0x1
#define DC_MOTOR_DIRECTION_BACKWARD		(uint8_t)0x2

/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/

/* Control the direction of the motor (Forward, Backward, Stop) */
void HDC_Motor_Direction(uint8_t u8Direction);

/* Control the speed of the motor using a PWM signal */
void HDC_Motor_Speed(uint16_t u16Speed);


#endif /* HDC_MOTOR_H_ */
