/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Lights.c
 *        \brief  Initialize and Set Lights State
 *
 *      \details  The Driver initialize the device with GPIO Pins and update the state of it
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Lights.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void initLights(void)
* \Description     : initialize Lights
*******************************************************************************/
void initLights(void)
{
	GPIO_init(LightsPort,RightLightPin,OUTPUT);
	GPIO_init(LightsPort,LeftLightPin,OUTPUT);
}

/******************************************************************************
* \Syntax          : void setLightsState(LightState_t Lights)
* \Description     : set the State of the Lights
*******************************************************************************/
void setLightState(LightState_t Lights)
{
	if(Lights == PIN_IS_HIGH)
	{
		GPIO_writePin(LightsPort,RightLightPin,PIN_IS_HIGH);
		GPIO_writePin(LightsPort,LeftLightPin,PIN_IS_HIGH);
	}
	else
	{
		GPIO_writePin(LightsPort,RightLightPin,PIN_IS_LOW);
		GPIO_writePin(LightsPort,LeftLightPin,PIN_IS_LOW);
	}
}

/******************************************************************************
* \Syntax          : LightState_t getLightState(void)
* \Description     : set the State of the Lights
*******************************************************************************/
LightState_t getLightState(void)
{
	if((GPIO_readPin(LightsPort,RightLightPin) ^ GPIO_readPin(LightsPort,LeftLightPin)) == 1)
		return 0xFF;
	else if(GPIO_readPin(LightsPort,RightLightPin) & GPIO_readPin(LightsPort,LeftLightPin))
		return PIN_IS_HIGH;
	else
		return PIN_IS_LOW;
}
/**********************************************************************************************************************
 *  END OF FILE: Lights.c
 *********************************************************************************************************************/
