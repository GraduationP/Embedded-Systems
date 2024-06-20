/*
 * CAN.c
 *
 *  Created on: Feb 25, 2024
 *      Author: wegz
 */

#include <Config.h>
#include <CAN.h>
#include <new_NMEA.h>
#include "HCompass_HMC5883L_3.h"

extern uint32_t volatile percentage;
extern uint32_t volatile temp;
extern GPSSTRUCT gpsdata;
extern compass_S compass;
extern float kp;
extern float ki;
extern float kd;

extern CAN_HandleTypeDef hcan;

uint32_t Txmailbox;
uint8_t Tx_can_data[8] ;
int8_t Rx_can_data[8];
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

int lane_dist = 90;
uint8_t nearest_dist;
uint8_t bump_detected;
int counter ;
int speed ;
int range;

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

		lane_dist 			= Rx_can_data[lane];
		nearest_dist 		= Rx_can_data[nearest_opj];
		bump_detected 		= Rx_can_data[bump];
//		kp 					= Rx_can_data[3];
//		ki			 		= Rx_can_data[4];
//		kd			 		= Rx_can_data[5];
	}


}


void can_tx(uint32_t ID , uint8_t DLC , uint8_t *payload)
{

	Tx_can_data[car_speed]		=speed;
	Tx_can_data[charge]			=percentage;
	Tx_can_data[temperature]	=temp;
	Tx_can_data[car_range]		=range;
	Tx_can_data[compass_angle]	=compass.direction;
	Tx_can_data[latitudee]		=gpsdata.ggastruct.lcation.latitude;
	Tx_can_data[longitduee]		=gpsdata.ggastruct.lcation.longitude;


	TxHeader.DLC 	= DLC;
	TxHeader.ExtId 	= CAN_ID_STD ;
	TxHeader.RTR 	= CAN_RTR_DATA ;
	TxHeader.StdId 	= ID ;


	if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan))
	{
		//		HAL_CAN_AddTxMessage(&hcan, &TxHeader, payload, &Txmailbox);
		HAL_CAN_AddTxMessage(&hcan, &TxHeader, payload, &Txmailbox);
	}

	while(HAL_CAN_IsTxMessagePending(&hcan, Txmailbox));

}
