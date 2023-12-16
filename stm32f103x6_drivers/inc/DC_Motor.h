/*
 * DC_Motor.h
 *
 *  Created on: Dec 15, 2023
 *      Author: Omar
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/**************************************/
/*				Includes			  */
/**************************************/
#include <stm32f103x6.h>
#include <gpio_driver.h>


/**************************************/
/*			DC Motor Structures	  	  */
/**************************************/
typedef struct {
	GPIOx_R* GPIOx;
	uint16_t GPIO_Pin;
}DC_Motor_PinConfig_S;


typedef struct{
	DC_Motor_PinConfig_S Motor_Pin1;
	DC_Motor_PinConfig_S Motor_Pin2;
	DC_Motor_PinConfig_S Motor_SpeedPin;
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




#endif /* DC_MOTOR_H_ */
