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
#define car_range		3
#define compass_angle	4
#define latitudee		5
#define longitduee		6

#define lane			0
#define nearest_opj		1
#define bump			2

extern uint8_t Tx_can_data[8] ;
extern int counter ;
extern int speed ;
extern int range;
extern int lane_dist;


void can_tx(uint32_t ID , uint8_t DLC , uint8_t *payload);
void can_rx();

#endif /* INC_CAN_H_ */
