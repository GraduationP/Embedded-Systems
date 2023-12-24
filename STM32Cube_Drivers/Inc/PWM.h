/*
 * PWM.h
 *
 *  Created on: Dec 23, 2023
 *      Author: Omar
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_



/**************************************/
/*				Includes		  	  */
/**************************************/
#include <stm32f1xx_hal_tim.h>


/**************************************/
/*			 PWM Structures	       	  */
/**************************************/
typedef struct{
	TIM_HandleTypeDef 	*htim;		    // Specific Timer to use for the servo from TIM1 to TIM4
	uint32_t			Channel;		// Timer Channel
								   	   //This parameter can be one of the following values:
								  	  //@arg TIM_CHANNEL_1: TIM Channel 1 selected
								 	 //@arg TIM_CHANNEL_2: TIM Channel 2 selected
									//@arg TIM_CHANNEL_3: TIM Channel 3 selected
							   	   //@arg TIM_CHANNEL_4: TIM Channel 4 selected
}TimerConf_TypeDef;


/**************************************/
/*		 	Macros References 	  	  */
/**************************************/


/**************************************/
/*		  Functions Prototypes 	  	  */
/**************************************/

/* Modifying the On Time of the PWM signal */
void PWM_ModifyOnTime(TimerConf_TypeDef *TimerConf, uint32_t u32Value);

/* Modifying the Period of the PWM signal */
void PWM_ModifyPeriod(TIM_HandleTypeDef* htim, uint32_t u32Period);

#endif /* INC_PWM_H_ */
