/*
 * STM32F401RE.h
 *
 *  Created on: Jul 24, 2023
 *      Author: abdom
 */

#ifndef INC_STM32F401RE_H_
#define INC_STM32F401RE_H_
//-----------------------------
//Includes
//-----------------------------
#include <stdint.h>
#include <stdlib.h>
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define SRAM1_base					0x20000000
#define System_memory_base			0x1FFF0000
#define Flash_memory_base			0x08000000
#define Flash_aliased_base			0x00000000
//-----------------------------
//Base addresses for BUS Peripherals
//-----------------------------
#define RCC_base			0x40023800
#define GPIOA_base			0x40020000
#define GPIOB_base			0x40020400
#define GPIOC_base			0x40020800
#define GPIOD_base			0x40020C00
#define GPIOE_base			0x40021000
#define EXTI_base			0x40013C00
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*

//RCC
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	uint32_t RESERVED;
	uint32_t RESERVED1;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	uint32_t RESERVED2;
	uint32_t RESERVED3;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	uint32_t RESERVED4;
	uint32_t RESERVED5;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	uint32_t RESERVED6;
	uint32_t RESERVED7;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	uint32_t RESERVED8;
	uint32_t RESERVED9;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	uint32_t RESERVED10;
	uint32_t RESERVED11;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	uint32_t RESERVED12;
	uint32_t RESERVED13;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	uint32_t RESERVED14;
	volatile uint32_t DCKCFGR;

}RCC_S;

//GPIO
typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
}GPIO_S;


//EXTI
typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_S;
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC 				((RCC_S *)RCC_base)

#define GPIOA 				((GPIO_S *)GPIOA_base)
#define GPIOB 				((GPIO_S *)GPIOB_base)
#define GPIOC 				((GPIO_S *)GPIOC_base)
#define GPIOD 				((GPIO_S *)GPIOD_base)
#define GPIOE 				((GPIO_S *)GPIOE_base)

#define EXTI 				((EXTI_S *) EXTI_base)
//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*-
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLK_EN()		(RCC->AHB1ENR |= 1<<0)
#define RCC_GPIOB_CLK_EN()		(RCC->AHB1ENR |= 1<<1)
#define RCC_GPIOC_CLK_EN()		(RCC->AHB1ENR |= 1<<2)
#define RCC_GPIOD_CLK_EN()		(RCC->AHB1ENR |= 1<<3)
#define RCC_GPIOE_CLK_EN()		(RCC->AHB1ENR |= 1<<4)

#define RCC_CRC_CLK_EN()		(RCC->AHB1ENR |= 1<<12)

#define RCC_DMA1_CLK_EN()		(RCC->AHB1ENR |= 1<<21)
#define RCC_DMA2_CLK_EN()		(RCC->AHB1ENR |= 1<<22)

#define RCC_USART1_CLK_EN()		(RCC->APB2ENR |= 1<<4)
#define RCC_USART6_CLK_EN()		(RCC->APB2ENR |= 1<<5)
#define RCC_USART2_CLK_EN()		(RCC->APB1ENR |= 1<<17)






#endif /* INC_STM32F401RE_H_ */
