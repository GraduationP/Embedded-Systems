/*
 * gpio_driver.c
 *
 *  Created on: Jul 15, 2023
 *      Author: abdom
 */


#include <stdint.h>
#include <stdlib.h>
#include <stm32f103x6.h>
#include <gpio_driver.h>

uint32_t pos(uint32_t pin)
{
	switch (pin)
	{
	case pin0 :
		return 0;
		break;
	case pin1 :
		return 4;
		break;
	case pin2 :
		return 8;
		break;
	case pin3 :
		return 12;
		break;
	case pin4 :
		return 16;
		break;
	case pin5 :
		return 20;
		break;
	case pin6 :
		return 24;
		break;
	case pin7 :
		return 28;
		break;
	case pin8 :
		return 0;
		break;
	case pin9 :
		return 4;
		break;
	case pin10 :
		return 8;
		break;
	case pin11 :
		return 12;
		break;
	case pin12 :
		return 16;
		break;
	case pin13 :
		return 20;
		break;
	case pin14 :
		return 24;
		break;
	case pin15 :
		return 28;
		break;
	}
	return 0;
}

void MCAL_GPIO_DEINIT		(GPIOx_R* GPIOx)
{
	if(GPIOx==GPIOA)
	{
		RCC->APB2RSTR |=  pin2;
		RCC->APB2RSTR &= ~pin2;
	}
	if(GPIOx==GPIOB)
	{
		RCC->APB2RSTR |=  pin3;
		RCC->APB2RSTR &= ~pin3;
	}
	if(GPIOx==GPIOC)
	{
		RCC->APB2RSTR |=  pin4;
		RCC->APB2RSTR &= ~pin4;
	}
	if(GPIOx==GPIOD)
	{
		RCC->APB2RSTR |=  pin5;
		RCC->APB2RSTR &= ~pin5;
	}
	if(GPIOx==GPIOE)
	{
		RCC->APB2RSTR |=  pin6;
		RCC->APB2RSTR &= ~pin6;
	}
}

uint8_t MCAL_GPIO_READPIN	(GPIOx_R* GPIOx , uint32_t pinNumper)
{
	if ((GPIOx->IDR & pinNumper) != 0 )
	{
		return 1 ;
	}
	return 0 ;
}

uint16_t MCAL_GPIO_READPORT	(GPIOx_R* GPIOx)
{
	return GPIOx->IDR & 0x0000ffff;
}

void MCAL_GPIO_WRITEPIN		(GPIOx_R* GPIOx , uint32_t pinNumper , uint8_t Value)
{
	switch (Value)
	{
	case 0 :
		GPIOx->BRR = pinNumper;
		break;
	case 1 :
		GPIOx->BSRR = pinNumper;
		break;
	}
}

void MCAL_GPIO_WRITEPORT  	(GPIOx_R* GPIOx , uint8_t Value)
{
	GPIOx->ODR = Value;
}

void MCAL_GPIO_TOGGLEPIN	(GPIOx_R* GPIOx , uint32_t pinNumper)
{
	GPIOx->ODR ^= pinNumper ;
}

//void MCAL_GPIO_LOCKPIN		(GPIOx_R* GPIOx , uint8_t pinNumper);


void MCAL_GPIO_INIT			(GPIOx_R* GPIOx , GPIO_PinConfig_t* PinConfig)
{
	volatile uint32_t *confreg =NULL ;
	confreg = ((PinConfig->GPIO_PinNumber)<pin8)? &GPIOx->CRL : &GPIOx->CRH ;
	*confreg &= ~(0xf<<pos(PinConfig->GPIO_PinNumber));
	if (PinConfig->GPIO_MODE<4)
	{
		switch (PinConfig->GPIO_MODE)
		{
		case GPIO_MODE_INPUT_FLOTING:
			*confreg |= PinConfig->GPIO_MODE << (pos(PinConfig->GPIO_PinNumber)+2);
			break;
		case GPIO_MODE_INPUT_PU:
			*confreg |= PinConfig->GPIO_MODE << (pos(PinConfig->GPIO_PinNumber)+2);
			GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			break;
		case GPIO_MODE_INPUT_PD:
			*confreg |= (PinConfig->GPIO_MODE-1) << (pos(PinConfig->GPIO_PinNumber)+2);
			GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			break;
		}
	}
	else
	{
//		bits = ((PinConfig->GPIO_MODE-4) << 2 )|(PinConfig->GPIO_PinNumber & 0x0f);
		*confreg |= (PinConfig->GPIO_MODE-4) << (pos(PinConfig->GPIO_PinNumber)+2);
		*confreg |= (PinConfig->GPIO_Output_Speed) << (pos(PinConfig->GPIO_PinNumber));


	}


}


