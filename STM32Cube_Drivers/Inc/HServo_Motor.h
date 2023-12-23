/*
 * HServo_Motor.h
 *
 *  Created on: Dec 23, 2023
 *      Author: Omar
 */

#ifndef INC_HSERVO_MOTOR_H_
#define INC_HSERVO_MOTOR_H_


/**************************************/
/*			Servo Structures	  	  */
/**************************************/
#include <Timerx_ConfTypes.h>


/**************************************/
/*		 	Macros References 	  	  */
/**************************************/


/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/

/* Initializing Servo Pin */
void HServo_Init(TimerPin_TypeDef* Servo_TimerConfig);

/* Writing the servo position (from 0 to 180) */
void HServo_writePosition(TimerPin_TypeDef* Servo_TimerConfig, uint8_t u8ServoPosition);

/* Writing a value in microseconds (us) to the servo */
void HServo_writeMicroseconds(TimerPin_TypeDef* Servo_TimerConfig, uint16_t u16Value);

/* Detaching the servo pin (Stopping PWM Signal) */
void HServo_DeInit(TimerPin_TypeDef* Servo_TimerConfig);

#endif /* INC_HSERVO_MOTOR_H_ */
