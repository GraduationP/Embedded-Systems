/*
 * Temperature_Battery.h
 *
 *  Created on: Feb 17, 2024
 *      Author: wegz
 */

#ifndef INC_TEMPERATURE_BATTERY_H_
#define INC_TEMPERATURE_BATTERY_H_

extern uint32_t adc[2];

extern uint32_t volatile percentage;
extern float volatile new_percentage;
extern uint32_t volatile temp;

//battery macros
#define tollerence 0.84

//Temperature macros
#define V25 1.43
#define VSENSE 3.3/4096
#define Avg_Slope 0.0043

float Read_Temperature();
uint32_t Read_Battery();

#endif /* INC_TEMPERATURE_BATTERY_H_ */
