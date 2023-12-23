/*
 * Timer_ConfTypes.h
 *
 *  Created on: Dec 23, 2023
 *      Author: Omar
 */



#ifndef INC_TIMERX_CONFTYPES_H_
#define INC_TIMERX_CONFTYPES_H_

#include <stm32f1xx_hal_tim.h>
#include <stm32f1xx_hal_gpio.h>


typedef struct {
	TIM_HandleTypeDef	 *htim;
	uint32_t 			 Channel;
}TimerPin_TypeDef;





#endif /* INC_TIMERX_CONFTYPES_H_ */
