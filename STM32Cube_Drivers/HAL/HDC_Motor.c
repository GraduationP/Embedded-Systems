/*
 * DC_Motor.c
 *
 *  Created on: Dec 15, 2023
 *      Author: Omar
 */

/**************************************/
/*				Includes			  */
/**************************************/
#include <stm32f1xx_ll_tim.h>
#include <stm32f1xx_hal_gpio.h>
#include <HDC_Motor.h>

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- HDC_Motor_Init
 * @brief		- Initializes the desired DC Motor pin
 * @param[in]	- DC_Motor_Config: Contains the DC Motor GPIO Port and Pin informations
 * @retval		- None
 * Note			-
 */
void HDC_Motor_Init(DC_Motor_Config_S* DC_Motor_Config)
{
	/* Getting Pin1 ready for initialization */
	GPIO_InitTypeDef GPIO_Pin1;

	/* Configuring the first pin */
	GPIO_Pin1.Pin  = DC_Motor_Config->Motor_Pin1.GPIO_Pin;
	GPIO_Pin1.Mode = GPIO_MODE_OUTPUT_PP;

	/* Loading GPIO Port */
	GPIO_TypeDef* GPIOx_1 = DC_Motor_Config->Motor_Pin1.GPIOx;

	/* Initializing the first pin */
	HAL_GPIO_Init(GPIOx_1, &GPIO_Pin1);

	//----------------------------------------------//

	/* Getting Pin2 ready for initialization */
	GPIO_InitTypeDef GPIO_Pin2;

	/* Configuring the second pin */
	GPIO_Pin2.Pin  = DC_Motor_Config->Motor_Pin2.GPIO_Pin;
	GPIO_Pin2.Mode = GPIO_MODE_OUTPUT_PP;

	/* Loading GPIO Port */
	GPIO_TypeDef* GPIOx_2 = DC_Motor_Config->Motor_Pin2.GPIOx;

	/* Initializing the second pin */
	HAL_GPIO_Init(GPIOx_2, &GPIO_Pin2);
}


/**========================================================
 * @Fn			- HDC_Motor_Direction
 * @brief		- Controls the direction of the DC Motor
 * @param[in]	- DC_Motor_Config: Contains the DC Motor GPIO Ports and Pins informations
 * @param[in]	- u8Direction: The direction of the DC Motor. Must be set @ref DC_MOTOR_DIRECTION_define
 * @retval		- None
 * Note			-
 */
void HDC_Motor_Direction(DC_Motor_Config_S* DC_Motor_Config, uint8_t u8Direction)
{
	/* Writing Direction of the first pin */
	GPIO_TypeDef* GPIOx_1       = DC_Motor_Config->Motor_Pin1.GPIOx;
	uint32_t Local_u8Pin1Number = DC_Motor_Config->Motor_Pin1.GPIO_Pin;
	uint8_t Local_u8Direction1  = u8Direction %2;	// First bit of the variable
	HAL_GPIO_WritePin(GPIOx_1, Local_u8Pin1Number, Local_u8Direction1);

	/* Writing Direction of the second pin */
	GPIO_TypeDef* GPIOx_2       = DC_Motor_Config->Motor_Pin2.GPIOx;
	uint32_t Local_u8Pin2Number = DC_Motor_Config->Motor_Pin2.GPIO_Pin;
	uint8_t Local_u8Direction2  = u8Direction >> 1;	// Second bit of the variable
	HAL_GPIO_WritePin(GPIOx_2, Local_u8Pin2Number, Local_u8Direction2);
}


/**========================================================
 * @Fn			- HDC_Motor_Speed
 * @brief		- Sets the speed of the DC Motor using a PWM signal
 * @param[in]	- DC_Motor_Config: Contains the DC Motor GPIO Port and Pin informations
 * @param[in]	- u32Speed: the speed of the DC Motor in PWM. Values between (0):(255)
 * @retval		- None
 * Note			-
 */
void HDC_Motor_Speed(DC_Motor_Config_S* DC_Motor_Config, uint16_t u16Speed)
{
	TimerConf_TypeDef SpeedPin_Conf = DC_Motor_Config->Motor_SpeedPin;
	PWM_ModifyOnTime(&SpeedPin_Conf, u16Speed);
}
