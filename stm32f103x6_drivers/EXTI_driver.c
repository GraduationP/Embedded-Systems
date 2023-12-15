/*
 * EXTI_driver.c
 *
 *  Created on: Jul 17, 2023
 *      Author: abdom
 */

#include <stm32f103x6.h>
#include <EXTI_driver.h>
#include <stdint.h>
#include <gpio_driver.h>
#include <math.h>

uint8_t getLog(uint16_t pin)
{
	uint8_t x =0;
	while (pin !=0)
	{
		x++;
		pin = pin >> 1;
	}
	return (x-1);
}

void MCAL_EXTI_INIT(EXTI_S *exti_conf)
{
	//1 - init pin as an input pin
	GPIO_PinConfig_t pin_conf ;
	pin_conf.GPIO_MODE = GPIO_MODE_INPUT_FLOTING;
	pin_conf.GPIO_PinNumber = exti_conf->EXTI_PIN;
	MCAL_GPIO_INIT(exti_conf->EXTI_PORT, &pin_conf);

	//2 - select the port of the pin
	AFIO->EXTICR[(getLog(exti_conf->EXTI_PIN)/4)] |= ((port(exti_conf->EXTI_PORT)& 0xf) << (getLog(exti_conf->EXTI_PIN)%4)*4);

	//3 -EXTI AVTIVATE STATE RISING OR FALLING
	switch (exti_conf->TRIGER_STATE)
	{
	case triger_rising :
		EXTI->RTSR |= exti_conf->EXTI_PIN;
		break;
	case triger_falling :
		EXTI->FTSR |= exti_conf->EXTI_PIN;
		break;
	case triger_rising_and_falling :
		EXTI->RTSR |= exti_conf->EXTI_PIN;
		EXTI->FTSR |= exti_conf->EXTI_PIN;
		break;
	}
	EXTI->IMR |= exti_conf->EXTI_PIN;

	//4 - IRQ mask enable in NVIC
	switch (exti_conf->EXTI_PIN)
	{
	case pin0 :
		NVIC_IRQ6_EXTI0_EN;
		break;
	case pin1 :
		NVIC_IRQ7_EXTI1_EN;
		break;
	case pin2 :
		NVIC_IRQ8_EXTI2_EN;
		break;
	case pin3 :
		NVIC_IRQ9_EXTI3_EN;
		break;
	case pin4 :
		NVIC_IRQ10_EXTI4_EN;
		break;
	case pin5 :
	case pin6 :
	case pin7 :
	case pin8 :
	case pin9 :
		NVIC_IRQ23_EXTI5_9_EN;
		break;
	case pin10 :
	case pin11 :
	case pin12 :
	case pin13 :
	case pin14 :
	case pin15 :
		NVIC_IRQ40_EXTI10_15_EN;
		break;
	}



}
void MCAL_EXTI_DEINIT(void)
{
	EXTI->IMR = 			0x00000000;
	EXTI->EMR = 			0x00000000;
	EXTI->FTSR = 			0x00000000;
	EXTI->SWIER = 			0x00000000;
	EXTI->PR = 				0xffffffff;
}


