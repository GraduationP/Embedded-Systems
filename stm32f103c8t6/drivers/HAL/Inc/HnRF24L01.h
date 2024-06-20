/*
 * NRF24L01.h
 *
 *  Created on: Jan 18, 2024
 *      Author: Omar
 */

#ifndef INC_HNRF24L01_H_
#define INC_HNRF24L01_H_

/**************************************/
/*				Includes			  */
/**************************************/

#include <stm32f1xx_hal.h>


/**************************************/
/*		 	Macros References 	  	  */
/**************************************/
extern SPI_HandleTypeDef 	hspi2;

#define NRF_SPI						hspi2

#define NRF_CE_PIN					GPIO_PIN_11
#define NRF_CE_PORT					GPIOB

#define NRF_CS_PIN					GPIO_PIN_10
#define NRF_CS_PORT					GPIOB

#define PIPE_NUMBER					DATA_PIPE1

/* Memory Map */
#define NRF_CONFIG					0x00
#define NRF_EN_AA					0x01
#define NRF_EN_RXADDR				0x02
#define NRF_SETUP_AW				0x03
#define NRF_SETUP_RETR				0x04
#define NRF_RF_CH					0x05
#define NRF_RF_SETUP				0x06
#define NRF_STATUS					0x07

#define NRF_RX_ADDR_P0				0x0A
#define NRF_RX_ADDR_P1				0x0B
#define NRF_RX_ADDR_P2				0x0C
#define NRF_RX_ADDR_P3				0x0D
#define NRF_RX_ADDR_P4				0x0E
#define NRF_RX_ADDR_P5				0x0F
#define NRF_TX_ADDR					0x10

#define NRF_RX_PW_P0				0x11
#define NRF_RX_PW_P1				0x12
#define NRF_RX_PW_P2				0x13
#define NRF_RX_PW_P3				0x14
#define NRF_RX_PW_P4				0x15
#define NRF_RX_PW_P5				0x16
#define NRF_FIFO_STATUS				0x17

/* Instruction Memories */
#define NRF_FLUSH_TX				0xE1
#define NRF_FLUSH_RX				0xE2
#define NRF_REUSE_TX_PL				0xE3
#define NRF_R_RX_PAYLOAD			0x61
#define NRF_W_TX_PAYLOAD			0xA0

/* Generic Macros */
#define TX_MODE						0x00
#define RX_MODE						0x01

#define TRANSMISSION_SUCCESSFULLY 	0x01
#define TRANSMISSION_FAILED			0x00

#define DATA_NOT_AVAILABLE			0x00
#define DATA_AVAILABLE				0x01

#define DATA_PIPE0					0x0
#define DATA_PIPE1					0x1
#define DATA_PIPE2					0x2
#define DATA_PIPE3					0x3
#define DATA_PIPE4					0x4
#define DATA_PIPE5					0x5

#define DATA_RATE_1MBPS				0x0
#define DATA_RATE_2MBPS				0x1
#define DATA_RATE_250KBPS			0x2
/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/

void HnRF24_Init();

void HnRF24_SetChannel(uint8_t Channel);

void HnRF24_SetDataRate(uint8_t DataRate);

void HnRF24_TxPipe(uint8_t* Address);

uint8_t HnRF24_Transmit(uint8_t* Data);

void HnRF24_RxPipe(uint8_t PipeNumber, uint8_t* Address);

void HnRF24_Receive(void* Data);

uint8_t HnRF24_DataAvailable();

void HnRF24_printRadioSettings();

void My_NRF24_Init();

#endif /* INC_HNRF24L01_H_ */
