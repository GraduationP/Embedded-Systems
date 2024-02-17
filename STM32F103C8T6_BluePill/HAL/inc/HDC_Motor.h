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
#define DC_MOTOR_STOP			(uint8_t)0x0
#define DC_MOTOR_FORWARD		(uint8_t)0x1
#define DC_MOTOR_BACKWARD		(uint8_t)0x2
#define DC_MOTOR_BRAKE			(uint8_t)0x3

/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/

/* Initializes the DC Motor PWM Pin */
void HDC_Motor_Timer_Init();

/* Control the direction of the motor (Forward, Backward, Stop, Brake) */
void HDC_Motor_Direction(uint8_t u8Direction);

/* Control the speed of the motor using a PWM signal */
void HDC_Motor_Speed(uint8_t u16Speed);

#endif /* HDC_MOTOR_H_ */
