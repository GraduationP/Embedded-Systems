/*
 * DC_Motor.c
 *
 *  Created on: Dec 15, 2023
 *      Author: Omar
 */

/**************************************/
/*				Includes			  */
/**************************************/
#include <stm32f103x6.h>
#include <DC_Motor.h>

/**************************************/
/*			Generic Functions		  */
/**************************************/



/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- HDC_Motor_Init
 * @brief		- Initializes the desired DC Motor pin
 * @param[in]	- Motor_Config: Contains the DC Motor GPIO Port and Pin informations
 * @retval		- None
 * Note			-
 */
void HDC_Motor_Init(DC_Motor_Config_S* Motor_Config)
{
	/* Getting Pin1 ready for initialization */
	GPIO_PinConfig_t GPIO_Pin1;

	/* Configuring the first pin */
	GPIO_Pin1.GPIO_PinNumber = Motor_Config->Motor_Pin1.GPIO_Pin;
	GPIO_Pin1.GPIO_MODE = GPIO_MODE_OUTPUT_PP;

	/* Loading GPIO Port */
	GPIOx_R* GPIOx_1 = Motor_Config->Motor_Pin1.GPIOx;

	/* Initializing the first pin */
	MCAL_GPIO_INIT(GPIOx_1, &GPIO_Pin1);

	//----------------------------------------------//

	/* Getting Pin2 ready for initialization */
	GPIO_PinConfig_t GPIO_Pin2;

	/* Configuring the second pin */
	GPIO_Pin2.GPIO_PinNumber = Motor_Config->Motor_Pin2.GPIO_Pin;
	GPIO_Pin2.GPIO_MODE = GPIO_MODE_OUTPUT_PP;

	/* Loading GPIO Port */
	GPIOx_R* GPIOx_2 = Motor_Config->Motor_Pin2.GPIOx;

	/* Initializing the second pin */
	MCAL_GPIO_INIT(GPIOx_2, &GPIO_Pin2);

	//----------------------------------------------//

	/* Getting the Speed Pin ready for initialization */
	GPIO_PinConfig_t GPIO_SpeedPin;

	/* Configuring the Speed Pin */
	GPIO_SpeedPin.GPIO_PinNumber = Motor_Config->Motor_Pin1.GPIO_Pin;
	GPIO_SpeedPin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;

	/* Loading GPIO Port */
	GPIOx_R* GPIOx_3 = Motor_Config->Motor_SpeedPin.GPIOx;

	/* Initializing the Speed Pin*/
	MCAL_GPIO_INIT(GPIOx_3, &GPIO_SpeedPin);
}


/**========================================================
 * @Fn			- HDC_Motor_Direction
 * @brief		- Controls the direction of the DC Motor
 * @param[in]	- Motor_Config: Contains the DC Motor GPIO Ports and Pins informations
 * @param[in]	- u8Direction: The direction of the DC Motor. Must be set @ref DC_MOTOR_DIRECTION_define
 * @retval		- None
 * Note			-
 */
void HDC_Motor_Direction(DC_Motor_Config_S* Motor_Config, uint8_t u8Direction)
{
	/* Writing Direction of the first pin */
	GPIOx_R* GPIOx_1 = Motor_Config->Motor_Pin1.GPIOx;
	uint32_t Local_u8Pin1Number = Motor_Config->Motor_Pin1.GPIO_Pin;
	uint8_t Local_u8Direction1 = u8Direction %2;	// First bit of the variable
	MCAL_GPIO_WRITEPIN(GPIOx_1, Local_u8Pin1Number, Local_u8Direction1);

	/* Writing Direction of the second pin */
	GPIOx_R* GPIOx_2 = Motor_Config->Motor_Pin2.GPIOx;
	uint32_t Local_u8Pin2Number = Motor_Config->Motor_Pin2.GPIO_Pin;
	uint8_t Local_u8Direction2 = u8Direction >> 1;	// Second bit of the variable
	MCAL_GPIO_WRITEPIN(GPIOx_2, Local_u8Pin2Number, Local_u8Direction2);
}


/**========================================================
 * @Fn			- HDC_Motor_Speed
 * @brief		- Sets the speed of the DC Motor using a PWM signal
 * @param[in]	- Motor_Config: Contains the DC Motor GPIO Port and Pin informations
 * @param[in]	- u8Speed: the speed of the DC Motor in PWM. Values between ():()
 * @retval		- None
 * Note			-
 */
void HDC_Motor_Speed(DC_Motor_Config_S* Motor_Config, uint8_t u8Speed)
{

}






