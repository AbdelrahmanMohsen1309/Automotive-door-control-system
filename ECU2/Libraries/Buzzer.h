/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Buzzer.h
 *       Module:  Initialize and Set Buzzer State
 *
 *  Description:  header file for Buzzer Device    
 *  
 *********************************************************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
 
#include "GPIO.h"
#include "CONFIGURATIONS.h"
#include "Common_Macros.h"

/**********************************************************************************************************************
 *  Global Enumurations and Structures
 *********************************************************************************************************************/
typedef unsigned char BuzzerState_t;

enum
{
	Buzzer_Off,
	Buzzer_On
};

struct Buzzer_t
{
	void (*initBuzzer)    (void);
	void (*setBuzzerState)(BuzzerState_t);
	BuzzerState_t (*getBuzzerState)(void);
};
/**********************************************************************************************************************
 *  FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void initBuzzer(void);
void setBuzzerState(BuzzerState_t Buzzer);
BuzzerState_t getBuzzerState(void);
/**********************************************************************************************************************
 *  END OF FILE: Buzzer.h
 *********************************************************************************************************************/

#endif /* BUZZER_H */

