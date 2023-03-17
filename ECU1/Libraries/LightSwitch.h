/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  LightSwitch.h
 *       Module:  Get Updates of Light Switch
 *
 *  Description:  header file for Light Switch Module    
 *  
 *********************************************************************************************************************/

#ifndef LIGHT_SWITCH_H
#define LIGHT_SWITCH_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
 
#include "GPIO.h"
#include "CONFIGURATIONS.h"
#include "Common_Macros.h"
#include "lpc21xx.h"

/**********************************************************************************************************************
 *  Global Enumurations and Structures
 *********************************************************************************************************************/
typedef unsigned char LightSwitchState_t;

struct LightSwitch_t
{
	void               (*initLightSwitch)    (void);
	LightSwitchState_t (*getSwitchState)(void);
};
/**********************************************************************************************************************
 *  FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void initLightSwitch(void);
LightSwitchState_t getSwitchState(void);

/**********************************************************************************************************************
 *  END OF FILE: LightSwitch.h
 *********************************************************************************************************************/

#endif /* LIGHT_SWITCH_H */
