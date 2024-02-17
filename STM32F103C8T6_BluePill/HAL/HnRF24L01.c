/*
 * NRF24L01.c
 *
 *  Created on: Jan 18, 2024
 *      Author: Omar
 */


/**************************************/
/*				Includes			  */
/**************************************/

#include <HnRF24L01.h>

/**************************************/
/*	Generic Function-like Macros	  */
/**************************************/

#define NRF_CS_ACTIVATE()		HAL_GPIO_WritePin(NRF_CS_PORT, NRF_CS_PIN, GPIO_PIN_RESET)
#define NRF_CS_DEACTIVATE() 	HAL_GPIO_WritePin(NRF_CS_PORT, NRF_CS_PIN, GPIO_PIN_SET)

#define NRF_CE_ACTIVATE()		HAL_GPIO_WritePin(NRF_CE_PORT, NRF_CE_PIN, GPIO_PIN_SET)
#define NRF_CE_DEACTIVATE()		HAL_GPIO_WritePin(NRF_CE_PORT, NRF_CE_PIN, GPIO_PIN_RESET)

/**************************************/
/*			Generic Functions		  */
/**************************************/

void nRF24_Write_Byte(uint8_t RegisterAddress, uint8_t Data)
{
	uint8_t buffer[2];

	/* Activating nRF Chip Select to select the device */
	NRF_CS_ACTIVATE();

	/* Assigning the Register Address and writing 1 on 5th bit to enter Write operation */
	buffer[0] = RegisterAddress | (1<<5);

	/* Assigning the Data to be written */
	buffer[1] = Data;

	/* Sending Data to nRF24L01 */
	HAL_StatusTypeDef ErrorState;
	ErrorState = HAL_SPI_Transmit(&NRF_SPI, buffer, 2, 1000);

	/* Releasing the nRF Chip select */
	NRF_CS_DEACTIVATE();
}

/* Write multiple Bytes to the nRF24 */
void nRF24_Write(uint8_t RegisterAddress, uint8_t* Data, uint8_t DataSize)
{
	/* Activating nRF Chip Select to select the device */
	NRF_CS_ACTIVATE();

	/* writing 1 on 5th bit to enter Write operation */
	RegisterAddress |= (1<<5);

	/* Sending Data to nRF24L01 */
	HAL_SPI_Transmit(&NRF_SPI, &RegisterAddress, 1, 1000);
	HAL_SPI_Transmit(&NRF_SPI, Data, DataSize, 1000);

	/* Releasing the nRF Chip select */
	NRF_CS_DEACTIVATE();
}

uint8_t nRF24_ReadByte(uint8_t RegisterAddress)
{
	uint8_t DataReading;

	/* Activating nRF Chip Select to select the device */
	NRF_CS_ACTIVATE();

	/* Accessing the Register */
	HAL_SPI_Transmit(&NRF_SPI, &RegisterAddress, 1, 1000);

	/* Reading from the specified register */
	HAL_SPI_Receive(&NRF_SPI, &DataReading, 1, 1000);

	/* Releasing the nRF Chip select */
	NRF_CS_DEACTIVATE();

	return DataReading;
}

/* Read multiple Bytes from the nRF24 */
void nRF24_Read(uint8_t RegisterAddress, uint8_t* Data, uint8_t DataSize)
{
	/* Activating nRF Chip Select to select the device */
	NRF_CS_ACTIVATE();

	/* Accessing the Register */
	HAL_SPI_Transmit(&NRF_SPI, &RegisterAddress, 1, 1000);

	/* Reading from the specified register */
	HAL_SPI_Receive(&NRF_SPI, Data, DataSize, 1000);

	/* Releasing the nRF Chip select */
	NRF_CS_DEACTIVATE();
}


void nRF24_SendCommand(uint8_t Command)
{
	/* Activating nRF Chip Select to select the device */
	NRF_CS_ACTIVATE();

	/* Accessing the Register */
	HAL_SPI_Transmit(&NRF_SPI, &Command, 1, 1000);

	/* Releasing the nRF Chip select */
	NRF_CS_DEACTIVATE();
}

void nRF24_DelayMicroSeconds(uint32_t uSec)
{
	uint32_t uSecVar = uSec;
	uSecVar = uSecVar* ((SystemCoreClock/1000000)/3);
	while(uSecVar--);
}
/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- HnRF24_Init
 * @brief		- Initializes the nRF24L01
 * @param[in]	- Mode: Whether the nRF24L01 is wanted as RX or TX
 * 				  Must be set as =>	RX_MODE or TX_MODE
 * @retval		- None
 * Note			-
 */
void HnRF24_Init()
{
	/* Disabling the chip before configuration */
	NRF_CE_DEACTIVATE();

	/*Disabling CRC */
	nRF24_Write_Byte(NRF_CONFIG, nRF24_ReadByte(NRF_CONFIG) & ~(1<<3));

	/* Setting up the Address Width as 5 Bytes */
	nRF24_Write_Byte(NRF_SETUP_AW, 0x03);

	/* Disabling Auto Retransmission (because already disabled auto acknowledgment) */
	nRF24_Write_Byte(NRF_SETUP_RETR, 0x00);

	/* Setting up RF Data rate = 1Mbps, RF Output Power = 0 dBm for higher power and longer distance */
	nRF24_Write_Byte(NRF_RF_SETUP, 0x06);

	/* Setting up the Channel Frequency to 2.402GHz */
	nRF24_Write_Byte(NRF_RF_CH, 0x2);

	/* Disabling Auto Acknowledgment */
	nRF24_Write_Byte(NRF_EN_AA, 0x00);
}

/**========================================================
 * @Fn			- HnRF24_SetChannel
 * @brief		- Sets the Frequency Channel to communicate with other nRFs
 * @param[in]	- Channel: The desired channel
 * 				  Must be set from 0 to 125 if data rate is 1MBPS
 * @retval		- None
 * Note			- Must be the same frequency the other nRF uses
 */
void HnRF24_SetChannel(uint8_t Channel)
{
	/* Setting up the Channel Frequency to 2.402GHz */
	nRF24_Write_Byte(NRF_RF_CH, Channel);
}

/**========================================================
 * @Fn			- HnRF24_SetDataRate
 * @brief		- Sets the Data air rate
 * @param[in]	- DataRate: Allowed DataRates =  { DATA_RATE_250KBPS , DATA_RATE_2MBPS , DATA_RATE_1MBPS }
 * @retval		- None
 * Note			-
 */
void HnRF24_SetDataRate(uint8_t DataRate)
{
	uint8_t Command_DataRate;

	/* Setting Data rate to default 1MBPS */
	Command_DataRate = nRF24_ReadByte(NRF_RF_SETUP) & 0xD7;

	if(DataRate == DATA_RATE_2MBPS)
	{
		/* 2 MBPS */
		nRF24_Write_Byte(NRF_RF_SETUP, Command_DataRate | (1<<3));
	}
	else if(DataRate == DATA_RATE_250KBPS)
	{
		/* 250 KBPS*/
		nRF24_Write_Byte(NRF_RF_SETUP, Command_DataRate | (1<<5));
	}
	else
	{
		/* 1 MBPS */
		nRF24_Write_Byte(NRF_RF_SETUP, Command_DataRate);
	}
}

/**========================================================
 * @Fn			- HnRF24_TxMode
 * @brief		- Setting up an nRF24 device as a transmitter
 * @param[in]	- Address: The address of the receiver in 5 Bytes
 * @param[in]	- Channel: Specific channel the nRF24 will operate on
 * 				  Must be set from 0 to 125 selectable channels
 * @retval		- None
 * Note			-
 */
void HnRF24_TxPipe(uint8_t* Address)
{
	/* Assigning the TX Address to the nRF24 */
	nRF24_Write(NRF_TX_ADDR, Address, 5);
	nRF24_Write(NRF_RX_ADDR_P0, Address, 5);

	/* Clearing TX_DS for next transmissions */
	uint8_t Status = nRF24_ReadByte(NRF_STATUS);
	Status |= 1<<5;
	nRF24_Write_Byte(NRF_STATUS, Status);
}



/**========================================================
 * @Fn			- HnRF24_Transmit
 * @brief		- Transmitting data through the nRF24L01
 * @param[in]	- Data: pointer to the data to be transmitted of size 32 Bytes
 * @retval		- TRANSMISSION_SUCCESSFULLY / TRANSMISSION_FAILED
 * Note			-
 */
uint8_t HnRF24_Transmit(uint8_t* Data)
{
	/* Disabling CE to start transmitting */
	NRF_CE_DEACTIVATE();

	/* Powering up the device */
	uint8_t Config = nRF24_ReadByte(NRF_CONFIG);
	Config |= 1<<1;

	/* Setting PRIM_RX bit to 0 for transmission */
	Config &= ~(1<<0);

	/* Writing to the Config Register the previous commands */
	nRF24_Write_Byte(NRF_CONFIG, Config);

	/* After Powering Up */
//	NRF24_DelayMicroSeconds(300);
	NRF24_DelayMicroSeconds(650);

	/* Flushing FIFOs */
	nRF24_SendCommand(NRF_FLUSH_RX);
	nRF24_SendCommand(NRF_FLUSH_TX);

	/* Activating nRF Chip Select to select the device */
	NRF_CS_ACTIVATE();
	/* Accessing the TX Payload to write the data there */
	uint8_t TX_Payload = NRF_W_TX_PAYLOAD;
	HAL_SPI_Transmit(&NRF_SPI, &TX_Payload, 1, 100);

	/* Sending the 32 Bytes Data to the nRF24 */
	HAL_SPI_Transmit(&NRF_SPI, (uint8_t*)Data, 32, 1000);

	/* Releasing the Chip */
	NRF_CS_DEACTIVATE();

	/* Pulsing the chip for transmitting the data */
	NRF_CE_ACTIVATE();
	//	nRF24_DelayMicroSeconds(200);
	NRF24_DelayMicroSeconds(650);
	NRF_CE_DEACTIVATE();

	uint32_t Timeout = 10;
	uint32_t FirstTick = HAL_GetTick();
	uint8_t Status = 0x00;

	/* Waiting a little while to send the payload */
	while(!(Status &(1<<5)) && (HAL_GetTick() - FirstTick < Timeout))
	{
		Status = nRF24_ReadByte(NRF_STATUS);
	}

	/* Checking if the Data was transmitted successfully by checking TX_DS Bit */
	if((Status &(1<<5)))
	{
		/* Clearing TX_DS for next transmissions */
		Status |= 1<<5;
		nRF24_Write_Byte(NRF_STATUS, Status);

		return TRANSMISSION_SUCCESSFULLY;
	}

	return TRANSMISSION_FAILED;
}


/**========================================================
 * @Fn			- HnRF24_RxMode
 * @brief		- Setting up an nRF24 device as a receiver
 * @param[in]	- Address: Address of the receiver of the nRF in 5 Bytes
 * 				  Must match the transmitter's address
 *
 * @param[in]	- Channel: Specific channel frequency the nRF24 will operate on
 * 				  Must be chosen from 0 to 125 selectable channels
 *
 * @retval		- None
 * Note			-
 */
void HnRF24_RxPipe(uint8_t PipeNumber, uint8_t* Address)
{
	/* Assigning the RX Address to the nRF24 RX Pipe */
	if(PipeNumber <2)
	{
		/* Pipe 0 and Pipe 1 have Width of 5 Bytes */
		nRF24_Write(NRF_RX_ADDR_P0 + PipeNumber, Address, 5);
	}
	else
	{
		/* Pipes from 2 to 5 address registers have width of 1 Byte */
		nRF24_Write(NRF_RX_ADDR_P0 + PipeNumber, Address, 1);
	}

	/* Enabling Data Pipe */
	uint8_t RX_DataPipe = nRF24_ReadByte(NRF_EN_RXADDR);
	RX_DataPipe |= 1<<PIPE_NUMBER;
	nRF24_Write_Byte(NRF_EN_RXADDR, RX_DataPipe);

	/* Setting the Payload size to 32 Bytes to receive */
	nRF24_Write_Byte(NRF_RX_PW_P0 + PipeNumber, 32);
}

/**========================================================
 * @Fn			- HnRF24_DataAvailable
 * @brief		- Checks if there is any data received in RX FIFO
 * @retval		- DATA_AVAILABLE / DATA_NOT_AVAILABLE
 * Note			-
 */
uint8_t HnRF24_DataAvailable()
{
	/* Powering up and setting to RX mode */
	nRF24_Write_Byte(NRF_CONFIG, nRF24_ReadByte(NRF_CONFIG) | 0x3);

	//Restore pipe 0 address if exists
	//	if(pipe0_reading_address)
	//		NRF24_write_registerN(REG_RX_ADDR_P0, (uint8_t *)(&pipe0_reading_address), 5);

	/* Flushing FIFOs */
	nRF24_SendCommand(NRF_FLUSH_RX);
	nRF24_SendCommand(NRF_FLUSH_TX);

	/* Setting CE HIGH to start listening */
	NRF_CE_ACTIVATE();

	//Wait for 130 uSec for the radio to come on
	//	nRF24_DelayMicroSeconds(400);
	NRF24_DelayMicroSeconds(650);

	/* Checking Status register for available data */
	uint8_t Status = nRF24_ReadByte(NRF_STATUS);

	/* Checking RF_DR (DataReady bit) and Pipe Number */
	if((Status & (1<<6)))
	{
		/* Clear the RX_DataReady FIFO interrupt pin */
		nRF24_Write_Byte(NRF_STATUS, (Status| 1<<6));

		return DATA_AVAILABLE;
	}
	return DATA_NOT_AVAILABLE;
}


/**========================================================
 * @Fn			- HnRF24_Receive
 * @brief		- Receives Data from another nRF
 * @param[in]	- Data: Pointer to the received data
 * @retval		- None
 * Note			-
 */
void HnRF24_Receive(void* Data)
{
	/* Activating nRF Chip Select to select the device */
	NRF_CS_ACTIVATE();

	/* Accessing the RX Payload where the data is received */
	uint8_t RX_Payload = NRF_R_RX_PAYLOAD;
	HAL_SPI_Transmit(&NRF_SPI, &RX_Payload, 1, 100);

	/* Getting the Data from the RX FIFO */
	HAL_SPI_Receive(&NRF_SPI, Data, 32, 100);

	/* Releasing the nRF Chip select */
	NRF_CS_DEACTIVATE();

	//	nRF24_DelayMicroSeconds(400);
	NRF24_DelayMicroSeconds(650);

	/* Clearing the RX FIFO */
	nRF24_SendCommand(NRF_FLUSH_RX);
}




void HnRF24_DebugRadioSettings(void)
{
	uint8_t reg8Val;
	reg8Val = nRF24_ReadByte(0x00);
	reg8Val = nRF24_ReadByte(0x01);
	reg8Val = nRF24_ReadByte(0x02);
	reg8Val = nRF24_ReadByte(0x03)&0x03;
	reg8Val +=2;
	reg8Val = nRF24_ReadByte(0x05);
	reg8Val = nRF24_ReadByte(0x06);
	uint8_t pipeAddrs[6];
	nRF24_Read(0x0A, pipeAddrs, 5);
	nRF24_Read(0x0A+1, pipeAddrs, 5);
	nRF24_Read(0x0A+2, pipeAddrs, 1);
	nRF24_Read(0x0A+3, pipeAddrs, 1);
	nRF24_Read(0x0A+4, pipeAddrs, 1);
	nRF24_Read(0x0A+5, pipeAddrs, 1);
	nRF24_Read(0x0A+6, pipeAddrs, 5);
	reg8Val = nRF24_ReadByte(0x11);
	reg8Val = nRF24_ReadByte(0x11+1);
	reg8Val = nRF24_ReadByte(0x11+2);
	reg8Val = nRF24_ReadByte(0x11+3);
	reg8Val = nRF24_ReadByte(0x11+4);
	reg8Val = nRF24_ReadByte(0x11+5);
}
