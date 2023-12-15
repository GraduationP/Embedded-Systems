/*
 * EXTI_driver.h
 *
 *  Created on: Jul 17, 2023
 *      Author: abdom
 */

#ifndef INC_EXTI_DRIVER_H_
#define INC_EXTI_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include<stdint.h>
#include<stdlib.h>
#include<stm32f103x6.h>
#include<gpio_driver.h>
//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct
{
	GPIOx_R* EXTI_PORT;
	uint16_t EXTI_PIN;
	uint8_t TRIGER_STATE;
}EXTI_S;
//-----------------------------
//Macros Configuration References
#define triger_rising 						0
#define triger_falling 						1
#define triger_rising_and_falling 			2

#define port(x)		(x==GPIOA)?0: \
					(x==GPIOB)?1: \
					(x==GPIOC)?2: \
					(x==GPIOD)?3: 0


#define EXTI0 		6
#define EXTI1 		7
#define EXTI2 		8
#define EXTI3 		9
#define EXTI4 		10
#define EXTI5 		23
#define EXTI6 		23
#define EXTI7 		23
#define EXTI8 		23
#define EXTI9 		23
#define EXTI10 		40
#define EXTI11		40
#define EXTI12		40
#define EXTI13		40
#define EXTI14		40
#define EXTI15		40

#define USART1_IRQ		37
#define USART2_IRQ		38
#define USART3_IRQ		39


#define NVIC_IRQ6_EXTI0_EN						(NVIC_ISER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_EN						(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_EN						(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_EN						(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_EN						(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_EN					(NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_EN					(NVIC_ISER1 |= 1<<8)

#define NVIC_IRQ6_EXTI0_DI						(NVIC_ICER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_DI						(NVIC_ICER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_DI						(NVIC_ICER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_DI						(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_DI						(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_DI					(NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_DI					(NVIC_ICER1 |= 1<<8)

#define NVIC_USART1_IRQ_15_EN					(NVIC_ISER1 |= 1<<(USART1_IRQ-32))
#define NVIC_USART2_IRQ_15_EN					(NVIC_ISER1 |= 1<<(USART2_IRQ-32))
#define NVIC_USART3_IRQ_15_EN					(NVIC_ISER1 |= 1<<(USART3_IRQ-32))

#define NVIC_USART1_IRQ_15_DI					(NVIC_ICER1 |= 1<<(USART1_IRQ-32))
#define NVIC_USART2_IRQ_15_DI					(NVIC_ICER1 |= 1<<(USART2_IRQ-32))
#define NVIC_USART3_IRQ_15_DI					(NVIC_ICER1 |= 1<<(USART3_IRQ-32))



#define EXTI_PENDING_PIN0_DIS 			(EXTI->PR |= pin0);
#define EXTI_PENDING_PIN1_DIS 			(EXTI->PR |= pin1);
#define EXTI_PENDING_PIN2_DIS			(EXTI->PR |= pin2);
#define EXTI_PENDING_PIN3_DIS			(EXTI->PR |= pin3);
#define EXTI_PENDING_PIN4_DIS 			(EXTI->PR |= pin4);
#define EXTI_PENDING_PIN5_DIS 			(EXTI->PR |= pin5);
#define EXTI_PENDING_PIN6_DIS			(EXTI->PR |= pin6);
#define EXTI_PENDING_PIN7_DIS 			(EXTI->PR |= pin7);
#define EXTI_PENDING_PIN8_DIS 			(EXTI->PR |= pin8);
#define EXTI_PENDING_PIN9_DIS 			(EXTI->PR |= pin9);
#define EXTI_PENDING_PIN10_DIS 			(EXTI->PR |= pin10);
#define EXTI_PENDING_PIN11_DIS 			(EXTI->PR |= piN11);
#define EXTI_PENDING_PIN12_DIS 			(EXTI->PR |= pin12);
#define EXTI_PENDING_PIN13_DIS 			(EXTI->PR |= pin13);
#define EXTI_PENDING_PIN14_DIS			(EXTI->PR |= pin14);
#define EXTI_PENDING_PIN15_DIS 			(EXTI->PR |= pin15);
//-----------------------------
/*@ref Module_REF_NAME_define
*/
/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
*
* ===============================================
*/
void MCAL_EXTI_INIT(EXTI_S *conf);
void MCAL_EXTI_DEINIT(void);
void MCAL_EXTI_UPDATE(EXTI_S *conf);


#endif /* INC_EXTI_DRIVER_H_ */
