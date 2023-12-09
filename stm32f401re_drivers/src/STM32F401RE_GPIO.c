/*
 * STM32F401RE_GPIO.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Omar Raafat
 */


/**************************************/
/*				Includes			  */
/**************************************/
#include <STM32F401RE_GPIO.h>


/**************************************/
/*			Generic Functions		  */
/**************************************/
uint16_t GetPinPosition(uint16_t uint16_PinNumber)
{
	switch(uint16_PinNumber)
	{
	case GPIO_PIN0:
		return 0;
		break;
	case GPIO_PIN1:
		return 1;
		break;
	case GPIO_PIN2:
		return 2;
		break;
	case GPIO_PIN3:
		return 3;
		break;
	case GPIO_PIN4:
		return 4;
		break;
	case GPIO_PIN5:
		return 5;
		break;
	case GPIO_PIN6:
		return 6;
		break;
	case GPIO_PIN7:
		return 7;
		break;
	case GPIO_PIN8:
		return 8;
		break;
	case GPIO_PIN9:
		return 9;
		break;
	case GPIO_PIN10:
		return 10;
		break;
	case GPIO_PIN11:
		return 11;
		break;
	case GPIO_PIN12:
		return 12;
		break;
	case GPIO_PIN13:
		return 13;
		break;
	case GPIO_PIN14:
		return 14;
		break;
	case GPIO_PIN15:
		return 15;
		break;
	};
	return 0;
}

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- MCAL_GPIO_Init
 * @brief		- Initializes the GPIOx PINy according to the specified Pin_Config
 * @param[in]	- GPIOx		 : specific GPIO Port (from A to D)
 * @param[in]	- Pin_Config : pointer to the struct GPIO_PinConfig_S that contains the Pin config informations
 * @retval		- None
 * Note			-
 */
void MCAL_GPIO_Init(GPIO_S* GPIOx, GPIO_PinConfig_S* PinConfig)
{
	/* Clearing the Two MODER[1:0] bits before configuration */
	GPIOx->MODER &= ~(0x3<< (GetPinPosition(PinConfig->GPIO_PinNumber) * 2));

	/* Checking whether the GPIO mode is an output ,input ,analog or alternate function using One Hot Encoding */
	/* If Pin #4 is 1 ===> It's an INPUT Pin */
	if(((PinConfig->GPIO_PinMode >> MODE_INPUT_ENCODE) %2)== 1)
	{
		/* Default MODER value as Input so no change needed here */
		// ----------------------------------------  //
	}
	/* If Pin #5 is 1 ===> It's an Analog Pin */
	else if(((PinConfig->GPIO_PinMode >> MODE_ANALOG_ENCODE) %2)== 1)
	{
		/* Initializing GPIO Pin as an Analog Pin ___ MODER[1:0] = 0b11*/
		GPIOx->MODER |= 0x3 <<GetPinPosition(PinConfig->GPIO_PinNumber);
	}
	/* If Pin #6 is 1 ===> It's an Output Pin */
	else if(((PinConfig->GPIO_PinMode >> MODE_OUTPUT_ENCODE) %2) == 1)
	{
		/* Initializing GPIO Pin as an Output Pin ___ GPIOx_MODER[1:0] = 0b11*/
		GPIOx->MODER |= 0x1 <<GetPinPosition(PinConfig->GPIO_PinNumber);

		/* Output Type Register (Push-Pull or Open Drain) */
		GPIOx->OTYPER |= PinConfig->GPIO_PinMode & (0x01 << GetPinPosition(PinConfig->GPIO_PinNumber));

		/* GPIO port output speed register (OSPEEDR)*/
		GPIOx->OSPEEDR |= PinConfig->GPIO_Output_Speed << ((GetPinPosition(PinConfig->GPIO_PinNumber) * 2));
	}
	/* If Pin #7 is 1 ===> It's an Alternate Function */
	else if(((PinConfig->GPIO_PinMode >> MODE_AF_ENCODE) %2) == 1)
	{
		/* Initializing GPIO Pin as an AF Pin ___ MODER[1:0] = 0b11*/
		GPIOx->MODER |= 0x2 <<GetPinPosition(PinConfig->GPIO_PinNumber);

	}
	/* GPIO port pull-up/pull-down register (GPIOx_PUPDR[1:0])*/
	if(((PinConfig->GPIO_PinMode >> MODE_ANALOG_ENCODE) %2) == 0) // Every other mode has pull-up, pull-down capability
	{
		/* Resetting the last configurations */
		GPIOx->PUPDR &= ~(0x3<< (GetPinPosition(PinConfig->GPIO_PinNumber) * 2));

		/* Configure Pull-up, or Pull-down */
		GPIOx->PUPDR |= (PinConfig->GPIO_PinMode >> MODE_PU_OR_PD) <<(GetPinPosition(PinConfig->GPIO_PinNumber) * 2);
	}
}

/**========================================================
 * @Fn			- MCAL_GPIO_DeInit
 * @brief		- Resets the GPIOx Ports (from A to D)
 * @param[in]	- GPIOx : specific GPIO peripheral selection
 * @retval		- None
 * Note			-
 */
void MCAL_GPIO_DeInit(GPIO_S* GPIOx)
{
	if(GPIOx == GPIOA)
	{
		RCC->AHB1RSTR |= 0x1;
		RCC->AHB1RSTR &= ~0x1;
	}
	else if(GPIOx == GPIOB)
	{
		RCC->AHB1RSTR |= 0x2;
		RCC->AHB1RSTR &= ~0x2;
	}
	else if(GPIOx == GPIOC)
	{
		RCC->AHB1RSTR |= 0x4;
		RCC->AHB1RSTR &= ~0x4;
	}
	else if(GPIOx == GPIOD)
	{
		RCC->AHB1RSTR |= 0x8;
		RCC->AHB1RSTR &= ~0x8;
	}
}

/**========================================================
 * @Fn			- MCAL_GPIO_ReadPin
 * @brief		- Reads the GPIOx Peripheral specified pin
 * @param[in]	- GPIOx		 : specific GPIO Port (from A to D)
 * @param[in]	- Pin_Number : GPIO Pin number to be read
 * @retval		- The input pin value (two values based on @ref GPIO_PIN_state
 * Note			-
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_S* GPIOx, uint16_t PinNumber)
{
	return (((GPIOx->IDR) & PinNumber) >> GetPinPosition(PinNumber));
}

/**========================================================
 * @Fn			- MCAL_GPIO_ReadPort
 * @brief		- Reads the GPIOx Port value
 * @param[in]	- GPIOx		 : specific GPIO Port (from A to D)
 * @retval		- The port reading
 * Note			- None
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_S* GPIOx)
{
	return GPIOx->IDR;
}

/**========================================================
 * @Fn			- MCAL_GPIO_WritePin
 * @brief		- writes the GPIOx pin value
 * @param[in]	- GPIOx : specific GPIO Port (from A to D)
 * @param[in]	- PinNumber : specific GPIO peripheral selection
 * @retval		- None
 * Note			- None
 */
void MCAL_GPIO_WritePin(GPIO_S* GPIOx, uint16_t PinNumber, uint8_t PinValue)
{
	if(PinValue == GPIO_PIN_HIGH)
	{
		/* Setting GPIO Pin */
		//	Bits 31:16 BRy: Port x reset bit y (y = 0..15)
		//	These bits are write-only and can be accessed in word, half-word or byte mode. A read to
		//	these bits returns the value 0x0000.
		//	0: No action on the corresponding ODRx bit
		//	1: Resets the corresponding ODRx bit
		//	Note: If both BSx and BRx are set, BSx has priority.
		GPIOx->BSRR = PinNumber;
	}
	else
	{
		/* Resetting GPIO Pin */
		//	Bits 15:0 BSy: Port x set bit y (y= 0..15)
		//	These bits are write-only and can be accessed in word, half-word or byte mode. A read to
		//	these bits returns the value 0x0000.
		//	0: No action on the corresponding ODRx bit
		//	1: Sets the corresponding ODRx bit
		GPIOx->BSRR = PinNumber<<16;
	}
}

/**========================================================
 * @Fn			- MCAL_GPIO_WritePort
 * @brief		- Write to the GPIOx Port
 * @param[in]	- GPIOx : specific GPIO Port (from A to D)
 * @param[in]	- PortValue: the value written to the port
 * @retval		- None
 * Note			- None
 */
void MCAL_GPIO_WritePort(GPIO_S* GPIOx, uint16_t PortValue)
{
	GPIOx->ODR = (uint32_t)PortValue;
}

/**========================================================
 * @Fn			- MCAL_GPIO_TogglePin
 * @brief		- Toggles the GPIOx specific pin
 * @param[in]	- GPIOx : specific GPIO Port (from A to D)
 * @param[in]	- PinNumber: desired pin to toggle
 * @retval		- None
 * Note			- None
 */
void MCAL_GPIO_TogglePin(GPIO_S* GPIOx, uint8_t PinNumber)
{
	GPIOx->ODR  ^= PinNumber;
}

