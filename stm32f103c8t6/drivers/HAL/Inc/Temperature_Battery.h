/*
 * Temperature_Battery.h
 *
 *  Created on: Feb 17, 2024
 *      Author: wegz
 */

#ifndef INC_TEMPERATURE_BATTERY_H_
#define INC_TEMPERATURE_BATTERY_H_

//variable that DMA use to store ADC channels
uint32_t adc[2];
// -------------------------------battery----------------------------
//battery variables
float volatile volt;
uint32_t volatile percentage;
float volatile new_percentage;

//battery macros
#define tollerence 0.84

// -------------------------------Temperature----------------------------

//Temperature variables
float volatile temp;

//Temperature macros
#define V25 1.43
#define VSENSE 3.3/4096
#define Avg_Slope 0.0043

float Read_Temperature();
uint32_t Read_Battery();

#endif /* INC_TEMPERATURE_BATTERY_H_ */
