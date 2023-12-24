/*
 * PWM.c
 *
 *  Created on: Dec 23, 2023
 *      Author: Omar
 */

/**************************************/
/*				Includes			  */
/**************************************/
#include <stm32f1xx_ll_tim.h>
#include <PWM.h>
#include <stdint.h>

/**************************************/
/*			Generic Functions		  */
/**************************************/



/**************************************/
/*			 APIs Functions		  	  */
/**************************************/


void PWM_ModifyOnTime(TimerConf_TypeDef *TimerConf, uint32_t u32Value)
{
	switch(TimerConf->Channel )
	{
	case TIM_CHANNEL_1:
		TimerConf->htim->Instance->CCR1 = u32Value;
		break;

	case TIM_CHANNEL_2:
		TimerConf->htim->Instance->CCR2 = u32Value;
		break;

	case TIM_CHANNEL_3:
		TimerConf->htim->Instance->CCR3 = u32Value;
		break;

	case TIM_CHANNEL_4:
		TimerConf->htim->Instance->CCR4 = u32Value;
		break;
	}
}




void PWM_ModifyPeriod(TIM_HandleTypeDef* htim, uint32_t u32Period)
{
	htim->Init.Period = u32Period;
	HAL_TIM_PWM_Init(htim);
}

