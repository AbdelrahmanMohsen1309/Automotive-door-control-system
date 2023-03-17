/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Lights.h
 *       Module:  Initialize and Set Lights State
 *
 *  Description:  header file for Lights    
 *  
 *********************************************************************************************************************/

#ifndef LIGHTS_H_
#define LIGHTS_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
 
#include "GPIO.h"
#include "CONFIGURATIONS.h"
#include "Common_Macros.h"

/**********************************************************************************************************************
 *  Global Enumurations and Structures
 *********************************************************************************************************************/
typedef unsigned char LightState_t;

enum
{
	Lights_Off,
	Lights_On
};


struct Lights_t
{
	void (*initLights)    (void);
	void (*setLightState)(LightState_t);
	LightState_t (*getLightState)(void);
};
/**********************************************************************************************************************
 *  FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void initLights(void);
void setLightState(LightState_t Lights);
LightState_t getLightState(void);
/**********************************************************************************************************************
 *  END OF FILE: Lights.h
 *********************************************************************************************************************/

#endif /* LIGHTS_H */

