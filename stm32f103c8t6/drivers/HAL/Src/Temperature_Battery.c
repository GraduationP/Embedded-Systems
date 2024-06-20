/*
 * Temperature_Battery.c
 *
 *  Created on: Feb 17, 2024
 *      Author: wegz
 */


//#include "stm32f4xx_hal.h"
#include <stm32f1xx_hal.h>
#include "Temperature_Battery.h"

float Read_Temperature()
{
	temp = ((V25 - VSENSE * adc[0]) / Avg_Slope) +25 ;
	return temp;
}
uint32_t Read_Battery()
{
	//	maping (0 , 18.8) (0 ,4096 )
	//  vin = input * (8.8/4096)
	volt = (adc[1] * (18.8/4096) ) * tollerence;
	//	maping (12 , 14.6)--->(0 , 100)
	//	output = output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start)
	new_percentage = (100  / (14.6 - 12)) * (volt - 12);
	(percentage > (uint32_t)new_percentage) ? percentage = new_percentage :percentage;
	(percentage >100) ? percentage = 100 :percentage;
	(percentage <0) ? percentage = 0 :percentage;
	return percentage;
}
