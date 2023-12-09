/*
 * STM32F401RE_EXTI.c
 *
 *  Created on: Dec 7, 2023
 *      Author: Omar
 */


/**************************************/
/*				Includes			  */
/**************************************/

#include<STM32F401RE_EXTI.h>
#include<STM32F401RE_GPIO.h>


/**************************************/
/*			Generic Variables		  */
/**************************************/

static void (*GP_ISR_Callback[15])(void);

/**************************************/
/*			Generic Macros			  */
/**************************************/

#define EXTI_GPIO_NUMBER_MAPPING(x)	  (	(x==GPIOA)?0:\
		(x==GPIOB)?1:\
				(x==GPIOC)?2:\
						(x==GPIOD)?3:0 )


/**************************************/
/*			Generic Functions		  */
/**************************************/

void Enable_NVIC(uint16_t IRQ_Number)
{
	switch(IRQ_Number)
	{
	case 0:
		EXTI0_IRQ_ENABLE();
		break;

	case 1:
		EXTI1_IRQ_ENABLE();
		break;

	case 2:
		EXTI2_IRQ_ENABLE();
		break;

	case 3:
		EXTI3_IRQ_ENABLE();
		break;

	case 4:
		EXTI4_IRQ_ENABLE();
		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		EXTI9_5_IRQ_ENABLE();
		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		EXTI15_10_IRQ_ENABLE();
		break;

	case 16:
		EXTI16_IRQ_ENABLE();
		break;

	case 17:
		EXTI17_IRQ_ENABLE();
		break;

	case 18:
		EXTI18_IRQ_ENABLE();
		break;

	case 21:
		EXTI21_IRQ_ENABLE();
		break;
	case 22:
		EXTI22_IRQ_ENABLE();
		break;
	}
}

void Disable_NVIC(uint16_t IRQ_Number)
{
	switch(IRQ_Number)
	{
	case 0:
		EXTI0_IRQ_DISABLE();
		break;

	case 1:
		EXTI1_IRQ_DISABLE();
		break;

	case 2:
		EXTI2_IRQ_DISABLE();
		break;

	case 3:
		EXTI3_IRQ_DISABLE();
		break;

	case 4:
		EXTI4_IRQ_DISABLE();
		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		EXTI9_5_IRQ_DISABLE();
		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		EXTI15_10_IRQ_DISABLE();
		break;

	case 16:
		EXTI16_IRQ_DISABLE();
		break;

	case 17:
		EXTI17_IRQ_DISABLE();
		break;

	case 18:
		EXTI18_IRQ_DISABLE();
		break;

	case 21:
		EXTI21_IRQ_DISABLE();
		break;
	case 22:
		EXTI22_IRQ_DISABLE();
		break;
	}
}

void Modify_EXTI(EXTI_PinConfig_S* EXTI_Config)
{
	/* Configure the GPIO Pin to be Floating Input */
	GPIO_PinConfig_S GPIO_Pin;
	GPIO_Pin.GPIO_PinMode = GPIO_MODE_INPUT_FLOATING;
	GPIO_Pin.GPIO_PinNumber = EXTI_Config->EXTI_Pin.GPIO_Pin;
	MCAL_GPIO_Init(EXTI_Config->EXTI_Pin.GPIO_Port, &GPIO_Pin);

	/* Update SYSCFG to choose which Line and which port of EXTI will be used */
	uint8_t EXTICR_Index = EXTI_Config->EXTI_Pin.EXTI_InputLineNumber / 4;
	uint8_t EXTICR_Position =  (EXTI_Config->EXTI_Pin.EXTI_InputLineNumber % 4) *4 ;
	SYSCFG->EXTICR[EXTICR_Index] &= ~((0xF) << EXTICR_Position);
	SYSCFG->EXTICR[EXTICR_Index] |= ((EXTI_GPIO_NUMBER_MAPPING(EXTI_Config->EXTI_Pin.GPIO_Port)) << EXTICR_Position);

	/* Reset Rising or Falling Trigger registers */
	EXTI->RTSR &= ~(0x1 << EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
	EXTI->FTSR &= ~(0x1 << EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);

	/* Update Rising or Falling Trigger registers */
	EXTI->FTSR |= (EXTI_Config->Trigger_Selection % 2) << EXTI_Config->EXTI_Pin.EXTI_InputLineNumber; 	// First bit of Trigger selection
	EXTI->RTSR |= (EXTI_Config->Trigger_Selection >> 1) <<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber; 	// Second bit of Trigger selection

	/* Update IRQ ISR */
	GP_ISR_Callback[EXTI_Config->EXTI_Pin.EXTI_InputLineNumber] = EXTI_Config->P_ISR_Callback;

	/* Enable/Disable IRQ and NVIC */
	if(EXTI_Config->IRQ_Enable == EXTI_IRQ_ENABLE)
	{
		/* Unmasking IRQ from Interrupt mask register */
		EXTI->IMR |= 1<<(EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);

		/* Enabling IRQ in NVIC */
		Enable_NVIC(EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
	}
	else
	{
		/* Disabling IRQ from Interrupt mask register */
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);

		/* Disabling IRQ in NVIC */
		Disable_NVIC(EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
	}
}

/**************************************/
/*			 APIs Functions		  	  */
/**************************************/

/**========================================================
 * @Fn			- MCAL_EXTI_GPIO_Init
 * @brief		- Initializes the External interrupt line number according to EXTI_Config
 * @param[in]	- EXTI_PinConfig set by @ref EXTI_define, @ref EXTI_TRIGGER_define, @ref EXTI_IRQ_define
 * @retval		- None
 * Note			- Must Enable RCC Clock for GPIO and Alternate Functions
 */
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_S* EXTI_Config)
{
	Modify_EXTI(EXTI_Config);
}

/**========================================================
 * @Fn			- MCAL_EXTI_GPIO_Modify
 * @brief		- Modifies the External interrupt line number according to EXTI_Config
 * @param[in]	- EXTI_PinConfig set by @ref EXTI_define, @ref EXTI_TRIGGER_define, @ref EXTI_IRQ_define
 * @retval		- None
 * Note			- Must Enable RCC Clock for GPIO and Alternate Functions
 */
void MCAL_EXTI_GPIO_Modify(EXTI_PinConfig_S* EXTI_Config)
{
	Modify_EXTI(EXTI_Config);
}


/**========================================================
 * @Fn			- MCAL_EXTI_GPIO_DeInit
 * @brief		- Resets the EXTI peripheral and NVIC (masking both)
 * @param[in]	- None
 * @retval		- None
 * Note			-
 */
void MCAL_EXTI_GPIO_DeInit()
{
	/* Resetting EXTI Peripheral */
	EXTI->IMR = (uint32_t)0x0;
	EXTI->EMR = (uint32_t)0x0;
	EXTI->RTSR = (uint32_t)0x0;
	EXTI->FTSR = (uint32_t)0x0;
	EXTI->SWIER = (uint32_t)0x0;
	EXTI->PR = (uint32_t)0x0067FFFF;

	/* Disabling NVIC IRQs */
	EXTI0_IRQ_DISABLE();
	EXTI1_IRQ_DISABLE();
	EXTI2_IRQ_DISABLE();
	EXTI3_IRQ_DISABLE();
	EXTI4_IRQ_DISABLE();
	EXTI9_5_IRQ_DISABLE();
	EXTI15_10_IRQ_DISABLE();
	EXTI16_IRQ_DISABLE();
	EXTI17_IRQ_DISABLE();
	EXTI18_IRQ_DISABLE();
	EXTI21_IRQ_DISABLE();
	EXTI22_IRQ_DISABLE();
}



/**************************************/
/*			 ISR Functions		  	  */
/**************************************/


void EXTI0_IRQHandler(void)
{
	/* Clear the pending bit by writing 1  */
	EXTI->PR |= 1<<0;
	/* Call the ISR */
	GP_ISR_Callback[0]();
}

void EXTI1_IRQHandler(void)
{
	/* Clear the pending bit by writing 1 */
	EXTI->PR |= 1<<1;
	/* Call the ISR */
	GP_ISR_Callback[1]();
}

void EXTI2_IRQHandler(void)
{
	/* Clear the pending bit by writing 1 */
	EXTI->PR |= 1<<2;
	/* Call the ISR */
	GP_ISR_Callback[2]();
}

void EXTI3_IRQHandler(void)
{
	/* Call the ISR */
	GP_ISR_Callback[3]();

	/* Clear the pending bit by writing 1 */
	EXTI->PR |= 1<<3;
}

void EXTI4_IRQHandler(void)
{
	/* Clear the pending bit by writing 1 */
	EXTI->PR |= 1<<4;
	/* Call the ISR */
	GP_ISR_Callback[4]();
}

void EXTI9_5_IRQHandler()
{
	if(EXTI->PR & 1<<5) { EXTI->PR |= 1<<5; GP_ISR_Callback[5]();}
	if(EXTI->PR & 1<<6) { EXTI->PR |= 1<<6; GP_ISR_Callback[6]();}
	if(EXTI->PR & 1<<7) { EXTI->PR |= 1<<7; GP_ISR_Callback[7]();}
	if(EXTI->PR & 1<<8) { EXTI->PR |= 1<<8; GP_ISR_Callback[8]();}
	if(EXTI->PR & 1<<9) { EXTI->PR |= 1<<9; GP_ISR_Callback[9]();}
}

void EXTI15_10_IRQHandler()
{
	if(EXTI->PR & 1<<10) { EXTI->PR |= 1<<10; GP_ISR_Callback[10]();}
	if(EXTI->PR & 1<<11) { EXTI->PR |= 1<<11; GP_ISR_Callback[11]();}
	if(EXTI->PR & 1<<12) { EXTI->PR |= 1<<12; GP_ISR_Callback[12]();}
	if(EXTI->PR & 1<<13) { EXTI->PR |= 1<<13; GP_ISR_Callback[13]();}
	if(EXTI->PR & 1<<14) { EXTI->PR |= 1<<14; GP_ISR_Callback[14]();}
	if(EXTI->PR & 1<<15) { EXTI->PR |= 1<<15; GP_ISR_Callback[15]();}
}

void EXTI16_PVD_IRQHandler()
{
	/* Clear the pending bit by writing 1 */
	EXTI->PR |= 1<<16;
	/* Call the ISR */
	GP_ISR_Callback[16]();
}

void EXTI17_RTC_Alarm_IRQHandler()
{
	/* Clear the pending bit by writing 1 */
	EXTI->PR |= 1<<17;
	/* Call the ISR */
	GP_ISR_Callback[17]();
}

void EXTI18_OTG_FS_WKUP_IRQHandler()
{
	/* Clear the pending bit by writing 1 */
	EXTI->PR |= 1<<18;
	/* Call the ISR */
	GP_ISR_Callback[18]();
}

void EXTI22_RTC_WKUP_IRQHandler()
{
	/* Clear the pending bit by writing 1 */
	EXTI->PR |= 1<<22;
	/* Call the ISR */
	GP_ISR_Callback[22]();
}


