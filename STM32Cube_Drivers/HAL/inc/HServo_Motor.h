/*
 * HServo_Motor.h
 *
 *  Created on: Dec 23, 2023
 *      Author: Omar
 */

#ifndef INC_HSERVO_MOTOR_H_
#define INC_HSERVO_MOTOR_H_


/**************************************/
/*				Includes		  	  */
/**************************************/
#include <stm32f1xx_hal_tim.h>
#include <PWM.h>
//#include <stdint.h>

/**************************************/
/*			Servo Structures	  	  */
/**************************************/



/**************************************/
/*		 	Macros References 	  	  */
/**************************************/


/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/

/* Initializing Servo Pin */
void HServo_Init(TimerConf_TypeDef *Servo_TimerConf);

/* Writing the servo position (from 0 to 180) */
void HServo_writePosition(TimerConf_TypeDef *Servo_TimerConf, uint8_t u8ServoPosition);

/* Writing a value in microseconds (us) to the servo */
void HServo_writeMicroseconds(TimerConf_TypeDef *Servo_TimerConf, uint16_t u16Value);

/* Detaching the servo pin (Stopping PWM Signal) */
void HServo_DeInit(TimerConf_TypeDef *Servo_TimerConf);

#endif /* INC_HSERVO_MOTOR_H_ */
