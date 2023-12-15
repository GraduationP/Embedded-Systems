/*
 * stm32f103x6.h
 *
 *  Created on: Jul 15, 2023
 *      Author: abdom
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-----------------------------
//Includes
#include<stdlib.h>
#include<stdint.h>
//-----------------------------
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_MEMORY_BASE 										0X08000000
#define SYSTEM_MEMORY_BASE 										0X1FFFF000
#define OPTION_BYTES_MEMORY_BASE 								0X1FFFF800
#define SRAM_MEMORY_BASE 										0X20000000
#define PERIPHERALS_MEMORY_BASE 								0X40000000
#define CORTEX_M3_INTERNAL_PERIPHERALS_MEMORY_BASE 				0XE0000000

#define NVIC_BASE 												0XE000E100
#define NVIC_ISER0								*(volatile uint32_t *)(NVIC_BASE + 0x0)
#define NVIC_ISER1								*(volatile uint32_t *)(NVIC_BASE + 0x4)
#define NVIC_ISER2								*(volatile uint32_t *)(NVIC_BASE + 0x8)

#define NVIC_ICER0								*(volatile uint32_t *)(NVIC_BASE + 0x80)
#define NVIC_ICER1								*(volatile uint32_t *)(NVIC_BASE + 0x84)
#define NVIC_ICER2								*(volatile uint32_t *)(NVIC_BASE + 0x88)
//-----------------------------
//Base addresses for BUS Peripherals
//-----------------------------
//RCC
#define RCC_BASE			0x40021000
//GPIO
#define GPIOA_BASE			0x40010800
#define GPIOB_BASE			0x40010C00
#define GPIOC_BASE			0x40011000
#define GPIOD_BASE			0x40011400
#define GPIOE_BASE			0x40011800
//AFIO
#define AFIO_BASE			0x40010000
//EXTI
#define EXTI_BASE			0x40010400

#define USART1_BASE				0x40013800
#define USART2_BASE				0x40004400
#define USART3_BASE				0x40004800

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*
//RCC
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
}RCC_R;

//GPIO
typedef struct{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIOx_R;

//AFIO
typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t AMPR;
	volatile uint32_t EXTICR[4];
	volatile uint32_t RESERVED;
	uint32_t APB1ENR;
	volatile uint32_t MAPR2;

}AFIO_R;

//EXTI

typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_R;

//USART

typedef struct{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_R;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
//GPIOX
#define GPIOA				((GPIOx_R *)GPIOA_BASE)
#define GPIOB				((GPIOx_R *)GPIOB_BASE)
#define GPIOC				((GPIOx_R *)GPIOC_BASE)
#define GPIOD				((GPIOx_R *)GPIOD_BASE)
#define GPIOE				((GPIOx_R *)GPIOE_BASE)
//AFIO
#define AFIO				((AFIO_R *)AFIO_BASE)
//EXTI
#define EXTI				((EXTI_R *)EXTI_BASE)
//RCC
#define RCC					((RCC_R *)RCC_BASE)
//USART
#define USART1				((USART_R *)USART1_BASE)
#define USART2				((USART_R *)USART2_BASE)
#define USART3				((USART_R *)USART3_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//GPIO EN
#define RCC_GPIOA_CLK_EN()		(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()		(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()		(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()		(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()		(RCC->APB2ENR |= 1<<6)
//AFIO EN
#define RCC_AFIO_CLK_EN()		(RCC->APB2ENR |= 1<<0)
//USART EN
#define RCC_USART2_CLK_EN()		(RCC->APB1ENR |= 1<<17)
#define RCC_USART3_CLK_EN()		(RCC->APB1ENR |= 1<<18)
#define RCC_USART1_CLK_EN()		(RCC->APB2ENR |= 1<<14)
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*



#endif /* INC_STM32F103X6_H_ */
