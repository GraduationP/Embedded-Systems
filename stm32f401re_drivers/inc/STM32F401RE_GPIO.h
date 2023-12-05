/*
 * GPIO.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Omar
 */

#ifndef STM32F401RE_GPIO_H_
#define STM32F401RE_GPIO_H_

/**************************************/
/*		Includes	      */
/**************************************/
#include "STM32F401XE.h"


/**************************************/
/* 	  Config Structures	      */
/**************************************/

typedef struct{
	uint16_t 	GPIO_PinNumber;		 // The GPIO Pin number to be configured, must be set @ref GPIO_PIN_define
	uint8_t		GPIO_PinMode;		 // The GPIO Pin mode for the specific pin, @ref GPIO_PINMODE_define
	uint8_t		GPIO_Output_Speed;   // The GPIO Output speed for the specified pin, @ref GPIO_OUTPUT_SPEED_define
}GPIO_PinConfig_S;


/**************************************/
/*	 Macros Config References     */
/**************************************/

//@ref GPIO_PIN_define
#define GPIO_PIN0		(uint16_t)0x0001
#define GPIO_PIN1		(uint16_t)0x0002
#define GPIO_PIN2		(uint16_t)0x0004
#define GPIO_PIN3		(uint16_t)0x0008
#define GPIO_PIN4		(uint16_t)0x0010
#define GPIO_PIN5		(uint16_t)0x0020
#define GPIO_PIN6		(uint16_t)0x0040
#define GPIO_PIN7		(uint16_t)0x0080
#define GPIO_PIN8		(uint16_t)0x0100
#define GPIO_PIN9		(uint16_t)0x0200
#define GPIO_PIN10		(uint16_t)0x0400
#define GPIO_PIN11		(uint16_t)0x0800
#define GPIO_PIN12		(uint16_t)0x1000
#define GPIO_PIN13		(uint16_t)0x2000
#define GPIO_PIN14		(uint16_t)0x4000
#define GPIO_PIN15		(uint16_t)0x8000
#define GPIO_PIN_ALL		(uint16_t)0xFFFF


//@ref GPIO_PINMODE_define (PinConfig->GPIO_PinMode)
/* One Hot Encoding the port modes */
// First Byte is the Specific GPIO Mode
// Second Byte is for General Modes (INPUT, ANALOG, OUTPUT, AF)
// Last Byte is for Pull-up, Pull-down (0(NO PU, PD), 1(PU), 2()PD
#define GPIO_MODE_INPUT_FLOATING		(uint16_t)0x010
#define GPIO_MODE_INPUT_PULLUP			(uint16_t)0x111
#define GPIO_MODE_INPUT_PULLDOWN		(uint16_t)0x212
#define GPIO_MODE_ANALOG			(uint16_t)0x023
#define GPIO_MODE_OUTPUT_PUSH_PULL		(uint16_t)0x044
#define GPIO_MODE_OUTPUT_OPEN_DRAIN		(uint16_t)0x045
#define GPIO_MODE_OUTPUT_OD_PU			(uint16_t)0x146
#define GPIO_MODE_OUTPUT_OD_PD			(uint16_t)0x247
#define GPIO_MODE_OUTPUT_PP_PU			(uint16_t)0x148
#define GPIO_MODE_OUTPUT_PP_PD			(uint16_t)0x249
#define GPIO_MODE_AF_PUSH_PULL			(uint16_t)0x08A
#define GPIO_MODE_AF_OPEN_DRAIN			(uint16_t)0x08B
#define GPIO_MODE_AF_PP_PU			(uint16_t)0x18C
#define GPIO_MODE_AF_PP_PD			(uint16_t)0x28D
#define GPIO_MODE_AF_OD_PU			(uint16_t)0x18E
#define GPIO_MODE_AF_OD_PD			(uint16_t)0x28F

/* Modes Encoding Bits */
#define MODE_INPUT_ENCODE			(uint8_t)0x4
#define MODE_ANALOG_ENCODE			(uint8_t)0x5
#define MODE_OUTPUT_ENCODE			(uint8_t)0x6
#define MODE_AF_ENCODE				(uint8_t)0x7

/* Pull-up or Pull-down Encoding Bit */
#define MODE_PU_OR_PD				(uint8_t)0x8



//@ref GPIO_OUTPUT_SPEED_define
#define GPIO_SPEED_LOW				(uint8_t)0x0
#define GPIO_SPEED_MEDIUM			(uint8_t)0x1
#define GPIO_SPEED_HIGH				(uint8_t)0x2
#define GPIO_SPEED_VERY_HIGH		 	(uint8_t)0x3

//@ref GPIO_PIN_state
#define GPIO_PIN_LOW				(uint8_t)0x0
#define GPIO_PIN_HIGH				(uint8_t)0x1


/**************************************/
/*	  Functions Prototypes        */
/**************************************/

/* Initialize the GPIO peripheral */
void MCAL_GPIO_Init(GPIO_S* GPIOx, GPIO_PinConfig_S* PinConfig);

/* Resetting the whole GPIOx Peripheral */
void MCAL_GPIO_DeInit(GPIO_S* GPIOx);

/* Reading the value from a GPIO Pin */
uint8_t MCAL_GPIO_ReadPin(GPIO_S* GPIOx, uint16_t PinNumber);

/* Reading GPIO Port */
uint16_t MCAL_GPIO_ReadPort(GPIO_S* GPIOx);

/* Writing to GPIO Pin */
void MCAL_GPIO_WritePin(GPIO_S* GPIOx, uint16_t PinNumber, uint8_t PinValue);

/* Writing to GPIO Port */
void MCAL_GPIO_WritePort(GPIO_S* GPIOx, uint16_t PortValue);

/* Toggle GPIO Pin */
void MCAL_GPIO_TogglePin(GPIO_S* GPIOx, uint8_t PinNumber);

#endif /* STM32F401RE_GPIO_H_ */
