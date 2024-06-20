/*
 * CAN.h
 *
 *  Created on: Feb 25, 2024
 *      Author: wegz
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_

#include <stm32f1xx_hal.h>

#define car_speed		0
#define charge			1
#define temperature		2
#define range			3
#define latitudee		4
#define longitduee		5

#define lane			0
#define nearest_opj		1
#define bump			2

extern CAN_HandleTypeDef hcan;

uint32_t Txmailbox;
uint8_t Tx_can_data[8] ;
uint8_t Rx_can_data[8];
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

uint8_t lane_dist;
uint8_t nearest_dist;
uint8_t bump_detected;



void can_tx(uint32_t ID , uint8_t DLC , uint8_t *payload);
void can_rx();

#endif /* INC_CAN_H_ */
