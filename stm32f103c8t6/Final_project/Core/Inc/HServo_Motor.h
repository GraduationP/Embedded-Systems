/*
 * HServo_Motor.h
 *
 *  Created on: Dec 23, 2023
 *      Author: Omar
 */

#ifndef INC_HSERVO_MOTOR_H_
#define INC_HSERVO_MOTOR_H_

/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/
#include <stm32f1xx_hal.h>

extern TIM_HandleTypeDef 	htim3;
#define SERVO_TIMER					htim3
#define SERVO_CHANNEL				TIM_CHANNEL_1
/* Initializes the Servo PWM Pin */
void HServo_Timer_Init();

/* Writing the servo position (from 0 to 180) */
void HServo_writePosition(uint8_t u8ServoPosition);

/* Writing a value in microseconds (us) to the servo */
void HServo_writeMicroseconds(uint16_t u16Value);

/* Detaching the servo pin (Stopping PWM Signal) */
void HServo_DeInit();

#endif /* INC_HSERVO_MOTOR_H_ */
