/*
 * gpio_driver.c
 *
 *  Created on: Jul 15, 2023
 *      Author: abdom
 */


#include <stdint.h>
#include <stdlib.h>
#include <uart_driver.h>
#include <EXTI_driver.h>
#include <gpio_driver.h>

int get_baud_rate()
{

}
void mcal_uart_init(UART_CONF* conf)
{
	USART_R* usart = conf->USARTx ;
	if(conf->USARTx == USART1)
		RCC_USART1_CLK_EN();
	else if(conf->USARTx == USART2)
		RCC_USART2_CLK_EN();
	else if(conf->USARTx == USART3)
		RCC_USART3_CLK_EN();
	//1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	usart->CR1 |= UART_UE ;
	//2. Program the M bit in USART_CR1 to define the word length.
	usart->CR1 |= conf->Length ;
	//3. Program the number of stop bits in USART_CR2.
	usart->CR2 |= conf->Stop_Bits;
	//4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
					//place. Configure the DMA register as explained in multibuffer communication.

	//5. Select the desired baud rate using the USART_BRR register.
	usart->BRR |= get_baud_rate(conf->Baud_Rate);
	//6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
	//6. Set the RE bit USART_CR1. This enables the receiver which begins searching for a start bit
	usart->CR1 |= conf->USART_MODE ;
	//7. select the parity mode
	usart->CR1 |= conf->Parity ;
	//8. flow ctrl
	usart->CR3 |= conf->hwFlowCtl ;
	//9. IRQ ENABLE
	if (conf->IRQ_Enable != UART_IRQ_EN_NONE)
	{
		usart->CR1 |= conf->IRQ_Enable ;
		if(conf->USARTx == USART1)
			NVIC_USART1_IRQ_15_EN;
		else if(conf->USARTx == USART2)
			NVIC_USART2_IRQ_15_EN;
		else if(conf->USARTx == USART3)
			NVIC_USART3_IRQ_15_EN;
	}
}

void mcal_uart_send_data(uint8_t DATA , USART_R* UARTx)
{
	while(! (UARTx->SR & 1<<7 ) );
	UARTx->DR = (DATA & (uint16_t)0xff);
}

void mcal_uart_receive_data(uint8_t* buffer ,USART_R* UARTx)
{
	while(! (UARTx->SR & 1<<5 ) );
	*buffer = UARTx->DR & (uint16_t) 0xff;
}

void mcal_uart_pin_init(USART_R* UARTx)
{

	if(UARTx == USART1)
	{
		GPIO_PinConfig_t cnf;
		cnf.GPIO_MODE = GPIO_MODE_INPUT_PU;
		cnf.GPIO_PinNumber = pin9;
		MCAL_GPIO_INIT(GPIOA, cnf)
		cnf.GPIO_PinNumber = pin10;
		MCAL_GPIO_INIT(GPIOA, cnf)
	}

}
