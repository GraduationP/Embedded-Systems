/*
 * Config.h
 *
 *  Created on: Jan 5, 2024
 *      Author: Omar
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

/**************************************/
/*				Includes			  */
/**************************************/
#include <stm32f1xx_ll_tim.h>
#include <stm32f1xx_hal_tim.h>
#include <stm32f1xx_hal_gpio.h>
#include <stm32f1xx_hal_i2c.h>
/**************************************/
/*		 	External Variables 	  	  */
/**************************************/

/* Timers */
//extern TIM_HandleTypeDef	htim4;	// Uncomment if using Timer4/
extern TIM_HandleTypeDef 	htim3;
extern TIM_HandleTypeDef 	htim2;

/* I2C */
extern I2C_HandleTypeDef 	hi2c1;

/* UART */
extern UART_HandleTypeDef 	huart1;

/* SPI */
extern SPI_HandleTypeDef 	hspi2;

/**************************************/
/*		 	Macros References 	  	  */
/**************************************/

/* Servo Macros */
#define SERVO_TIMER					htim3
#define SERVO_CHANNEL				TIM_CHANNEL_1

/* DC Motor Macros */
#define DC_MOTOR_TIMER				htim2
#define DC_MOTOR_CHANNEL			TIM_CHANNEL_2

#define DC_MOTOR_PIN1				GPIO_PIN_1
#define DC_MOTOR_PIN1_GPIO			GPIOB

#define DC_MOTOR_PIN2				GPIO_PIN_0
#define DC_MOTOR_PIN2_GPIO			GPIOB

/* Used I2C Line */
#define I2C_BUS						hi2c1


/* GPS Macros */


/* NRF Macros */


/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/

/* Function to Start all of the hardware components*/
void Hardware_Start();

#endif /* INC_CONFIG_H_ */
