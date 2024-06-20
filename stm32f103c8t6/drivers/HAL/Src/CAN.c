/*
 * CAN.c
 *
 *  Created on: Feb 25, 2024
 *      Author: wegz
 */

#include <Config.h>
#include <CAN.h>
#include "HCompass_HMC5883L_3.h"
#include "HEncoderAS5600.h"
#include "HnRF24L01.h"
#include "new_NMEA.h"
#include "Temperature_Battery.h"



void can_rx()
{
	//(#) Reception:
	//(++) Monitor reception of message using HAL_CAN_GetRxFifoFillLevel()
	//until at least one message is received.
	//(++) Then get the message using HAL_CAN_GetRxMessage().

	if(HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO1))
	{
		//HAL_StatusTypeDef HAL_CAN_GetRxMessage(CAN_HandleTypeDef *hcan, uint32_t RxFifo, CAN_RxHeaderTypeDef *pHeader, uint8_t aData[])
		HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO1, &RxHeader, Rx_can_data);
	}
	lane_dist = 		Rx_can_data[lane];
	nearest_dist = 		Rx_can_data[nearest_opj];
	bump_detected = 	Rx_can_data[bump];


}


void can_tx(uint32_t ID , uint8_t DLC , uint8_t *payload)
{

	Tx_can_data[car_speed]	=90;
	Tx_can_data[charge]		=percentage;
	Tx_can_data[temperature]=temp;
	Tx_can_data[range]		=90;
	Tx_can_data[latitudee]	=gpsdata.ggastruct.lcation.latitude;
	Tx_can_data[longitduee]	=gpsdata.ggastruct.lcation.longitude;


	TxHeader.DLC = DLC;
	TxHeader.ExtId = CAN_ID_STD ;
	TxHeader.RTR = CAN_RTR_DATA ;
	TxHeader.StdId = ID ;


	if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan))
	{
		//		HAL_CAN_AddTxMessage(&hcan, &TxHeader, payload, &Txmailbox);


		HAL_CAN_AddTxMessage(&hcan, &TxHeader, payload, &Txmailbox);
	}

	while(HAL_CAN_IsTxMessagePending(&hcan, Txmailbox));

}
