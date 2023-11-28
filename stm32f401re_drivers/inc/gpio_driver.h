/*
 * gpio_driver.h
 *
 *  Created on: Jul 15, 2023
 *      Author: abdom
 */

#ifndef INC_GPIO_DRIVER_H_
#define INC_GPIO_DRIVER_H_

//-----------------------------
//Includes
#include <stdint.h>
#include <stdlib.h>
#include <stm32f103x6.h>
//-----------------------------
//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct{
	uint32_t GPIO_PinNumber ;
	uint8_t GPIO_MODE ;
	uint8_t GPIO_Output_Speed ;
}GPIO_PinConfig_t;
//-----------------------------
//Macros Configuration References
//-----------------------------
/*@ref GPIO_PINS_define
*/
#define pin0	(uint32_t)0x1
#define pin1	(uint32_t)0x2
#define pin2	(uint32_t)0x4
#define pin3	(uint32_t)0x8
#define pin4	(uint32_t)0x10
#define pin5	(uint32_t)0x20
#define pin6	(uint32_t)0x40
#define pin7	(uint32_t)0x80
#define pin8	(uint32_t)0x100
#define pin9	(uint32_t)0x200
#define pin10	(uint32_t)0x400
#define pin11	(uint32_t)0x800
#define pin12	(uint32_t)0x1000
#define pin13	(uint32_t)0x2000
#define pin14	(uint32_t)0x4000
#define pin15	(uint32_t)0x8000
#define allpins	(uint32_t)0xFFFF
/*
/*@ref GPIO_MODE_define
*/
//In input mode (MODE[1:0]=00):
//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: Input with pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
#define GPIO_MODE_INPUT_ANALOG			0X0
#define GPIO_MODE_INPUT_FLOTING			0X1
#define GPIO_MODE_INPUT_PU				0X2
#define GPIO_MODE_INPUT_PD				0X3
#define GPIO_MODE_OUTPUT_PP				0X4
#define GPIO_MODE_OUTPUT_OD				0X5
#define GPIO_MODE_OUTPUT_AF_PP			0X6
#define GPIO_MODE_OUTPUT_AF_OD			0X7
//#define GPIO_MODE_ANALOG				0X8
/*
/*@ref GPIO_SPEED_define
*/
//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz.
#define GPIO_SPEED_10_MHZ			0x1
#define GPIO_SPEED_2_MHZ			0x2
#define GPIO_SPEED_50_MHZ			0x3
/*

* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void MCAL_GPIO_INIT			(GPIOx_R* GPIOx , GPIO_PinConfig_t* PinConfig);
void MCAL_GPIO_DEINIT		(GPIOx_R* GPIOx);
uint8_t MCAL_GPIO_READPIN	(GPIOx_R* GPIOx , uint32_t pinNumper);
uint8_t MCAL_GPIO_READPORT	(GPIOx_R* GPIOx);
void MCAL_GPIO_WRITEPIN		(GPIOx_R* GPIOx , uint32_t pinNumper , uint8_t Value);
void MCAL_GPIO_WRITEPORT  	(GPIOx_R* GPIOx , uint8_t Value);
void MCAL_GPIO_TOGGLEPIN	(GPIOx_R* GPIOx , uint32_t pinNumper);
void MCAL_GPIO_LOCKPIN		(GPIOx_R* GPIOx , uint32_t pinNumper);

#endif /* INC_GPIO_DRIVER_H_ */
