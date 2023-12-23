/*
 * DC_Motor.h
 *
 *  Created on: Dec 15, 2023
 *      Author: Omar
 */

#ifndef INC_HDC_MOTOR_H_
#define INC_HDC_MOTOR_H_

/**************************************/
/*				Includes			  */
/**************************************/
#include <Timerx_ConfTypes.h>


/**************************************/
/*			DC Motor Structures	  	  */
/**************************************/
typedef struct {
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}DC_Motor_PinConfig_S;


typedef struct{
	DC_Motor_PinConfig_S Motor_Pin1;
	DC_Motor_PinConfig_S Motor_Pin2;
	TimerPin_TypeDef Motor_SpeedPin;
}DC_Motor_Config_S;

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

/* Initialize the DC Motor Control Pin */
void HDC_Motor_Init(DC_Motor_Config_S* Motor_Config);

/* Control the direction of the motor (Forward, Backward) */
void HDC_Motor_Direction(DC_Motor_Config_S* Motor_Config, uint8_t u8Direction);

/* Control the speed of the motor using a PWM signal */
void HDC_Motor_Speed(DC_Motor_Config_S* Motor_Config, uint8_t u8Speed);


#endif /* HDC_MOTOR_H_ */
