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

/**========================================================
 * @Fn			- PWM_ModifyOnTime
 * @brief		- Changing the Duty Cycle of the PWM by modifying the On_Time
 * @param[in]	- TimerConf: Contains the specific timer pin informations
 * @param[in]	- u32Value: On_Time value for the PWM
 * @retval		- None
 * Note			-
 */
void PWM_ModifyOnTime(TimerConf_TypeDef *TimerConf, uint16_t u16Value)
{
	switch(TimerConf->Channel )
	{
	case TIM_CHANNEL_1:
		TimerConf->htim->Instance->CCR1 = u16Value;
		break;

	case TIM_CHANNEL_2:
		TimerConf->htim->Instance->CCR2 = u16Value;
		break;

	case TIM_CHANNEL_3:
		TimerConf->htim->Instance->CCR3 = u16Value;
		break;

	case TIM_CHANNEL_4:
		TimerConf->htim->Instance->CCR4 = u16Value;
		break;
	}
}



/**========================================================
 * @Fn			- PWM_ModifyPeriod
 * @brief		- Changing the Period of the PWM signal
 * @param[in]	- htim: Contains the time configurations
 * @param[in]	- u16Period: Desired PWM Period	(0-65535)
 * @retval		- None
 * Note			-
 */
void PWM_ModifyPeriod(TIM_HandleTypeDef* htim, uint32_t u16Period)
{
	htim->Init.Period = u16Period;
	HAL_TIM_PWM_Init(htim);
}

