/*
 * UART_driver.h
 *
 *  Created on: Jul 15, 2023
 *      Author: abdom
 */

#ifndef INC_UART_DRIVER_H_
#define INC_UART_DRIVER_H_

#include <stdint.h>
#include <stdlib.h>
#include <stm32f103x6.h>

////////////////////////////////////Transmitter////////////////////////////////////////////////////
//1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
//2. Program the M bit in USART_CR1 to define the word length.
//3. Program the number of stop bits in USART_CR2.
//4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
//place. Configure the DMA register as explained in multibuffer communication.
//5. Select the desired baud rate using the USART_BRR register.
//6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
//7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
//for each data to be transmitted in case of single buffer.
//8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
//that the transmission of the last frame is complete. This is required for instance when
//the USART is disabled or enters the Half mode to avoid corrupting the last
//transmission.
typedef struct{

	USART_R* USARTx;
	uint32_t Baud_Rate;			//@REF BAUD_RATE_SELECTION
	uint8_t Parity;				//@REF BARITY_MODE
	uint8_t Stop_Bits;			//@REF STOP_BITS_NUMBER
	uint8_t USART_MODE;			//@REF usart_mode
	uint8_t Length;				//@REF DATA_LENGTH
	uint8_t hwFlowCtl;			//@REF hw flow control
	uint8_t IRQ_Enable;			//@REF UART_IRQ_EN

}UART_CONF;


////////////////////@REF BAUD_RATE_SELECTION///////////////////////
#define UART_BAUD_RATE_2400							2400
#define UART_BAUD_RATE_9600							9600
#define UART_BAUD_RATE_19200						19200
#define UART_BAUD_RATE_57600						57600
#define UART_BAUD_RATE_115200						115200
#define UART_BAUD_RATE_230400						230400
#define UART_BAUD_RATE_460800						460800
#define UART_BAUD_RATE_921600						921600
#define UART_BAUD_RATE_2250000						2250000
#define UART_BAUD_RATE_4500000						4500000


////////////////////@REF BARITY_MODE///////////////////////
#define UART_BARITY_NON						(uint32_t) (0)
#define UART_BARITY_EVEN					(uint32_t) (1<<10)
#define UART_BARITY_ODD						((uint32_t)(1<<10 | 1<<9))

////////////////////@REF STOP_BITS_NUMBER//////////////////
#define UART_STOP_BITS_HALF					(uint32_t) (1<<12)
#define UART_STOP_BITS_1					(uint32_t) (0)
#define UART_STOP_BITS_1_HALF				(uint32_t) (3<<12)
#define UART_STOP_BITS_2					(uint32_t) (2<<12)


////////////////////@REF usart_mode//////////////////////
#define UART_MODE_RX				(uint32_t) (1<<2)
#define UART_MODE_tX				(uint32_t) (1<<3)
#define UART_MODE_RX_TX				((uint32_t) (1<<2 | 1<<3))

/////////////////////@REF DATA_LENGTH/////////////////////
#define UART_DATA_BITS_8				(uint32_t) (0)
#define UART_DATA_BITS_9				(uint32_t) (1<<12)

////////////////////@REF hw flow control//////////////////
#define UART_flow_ctl_NON					(uint32_t) (0)
#define UART_flow_ctl_CTS					(uint32_t) (1<<9)
#define UART_flow_ctl_RTS					(uint32_t) (1<<8)
#define UART_flow_ctl_CTS_RTS				((uint32_t) (1<<8 | 1<<9))

////////////////////@REF UART_IRQ_EN/////////////////////
#define UART_IRQ_EN_NONE					(uint32_t) (0)
#define UART_IRQ_EN_TXE						(uint32_t) (1<<7)
#define UART_IRQ_EN_TC						(uint32_t) (1<<6)
#define UART_IRQ_EN_RXNEIE					(uint32_t) (1<<5)
#define UART_IRQ_EN_PE						(uint32_t) (1<<8)



#define UART_UE								(uint32_t) (1<<13)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mcal_uart_init(UART_CONF* conf);
void mcal_uart_send_data(uint8_t DATA , USART_R* UARTx);
void mcal_uart_receive_data(uint8_t* buffer ,USART_R* UARTx);
void mcal_uart_pin_init(USART_R* UARTx);


#endif /* INC_UART_DRIVER_H_ */
