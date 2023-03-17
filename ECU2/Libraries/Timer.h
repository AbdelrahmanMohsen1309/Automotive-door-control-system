/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Timer.h
 *       Module:  Timer Module
 *
 *  Description:  Header file for Timer Module    
 *  
 *********************************************************************************************************************/
#ifndef TIMER_H
#define TIMER_H


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "lpc21xx.h"
#include "Common_Macros.h"

/**********************************************************************************************************************
 *  Global Enumurations and Structures (Configuration Options)
 *********************************************************************************************************************/
/*Enum for Disable and enable Timer*/
enum{Timer_DISABLE          , Timer_ENABLE};

/*Enum for Disable and enable Timer interrupt*/
enum{Timer_INTERRUPT_DISABLE, Timer_INTERRUPT_ENABLE};

typedef void(*CB_type)(void);

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void Timer_Handler(void);
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void TimerEnable (void)                                      
* \Description     : This function starts the Timer counter. 
*                    If an interrupt handler has been registered, 
*                    it is called when the Timer counter rolls over.
*******************************************************************************/
void 	TimerEnable (void);


/******************************************************************************
* \Syntax          : void 	TimerDisable (void)
* \Description     : This function stops the Timer counter. 
*                    If an interrupt handler has been registered, 
*                    it is not called until Timer is restarted.
*******************************************************************************/
void 	TimerDisable (void);


/******************************************************************************
* \Syntax          : void 	TimerIntRegister (CB_type pfnHandler)
* \Description     : This function registers the handler to be called 
*                    when a Timer interrupt occurs.
*******************************************************************************/
void 	TimerIntRegister (CB_type pfnHandler);


/******************************************************************************
* \Syntax          : void 	TimerIntUnregister (void)
* \Description     : This function unregisters the handler to be called 
*                    when a Timer interrupt occurs.
*******************************************************************************/
void 	TimerIntUnregister (void);


/******************************************************************************
* \Syntax          : void 	TimerIntEnable (void)
* \Description     : This function enables the Timer interrupt, 
*                    allowing it to be reflected to the processor.
*******************************************************************************/
void 	TimerIntEnable (void);


/******************************************************************************
* \Syntax          : void 	TimerIntDisable (void)
* \Description     : This function disables the Timer interrupt, 
*                    preventing it from being reflected to the processor.
*******************************************************************************/
void 	TimerIntDisable (void);


/******************************************************************************
* \Syntax          : void 	TimerPeriodSet (uint32 ui32Period);
* \Description     : This function sets the rate at which the Timer counter 
*                    wraps, which equates to the number of processor clocks 
*                    between interrupts.                                    
*******************************************************************************/
void 	TimerPeriodSet (uint32 ui32Period);


/******************************************************************************
* \Syntax          : uint32 	TimerPeriodGet (void)
* \Description     : This function returns the rate at which the Timer counter 
*                    wraps, which equates to the number of processor clocks 
*                    between interrupts.  
*******************************************************************************/
uint32 	TimerPeriodGet (void);


/******************************************************************************
* \Syntax          : uint32 	TimerValueGet (void)
* \Description     : This function returns the current value of the Timer 
*                    counter, which is a value between the period - 1 and zero, 
*                    inclusive.                                    
*******************************************************************************/
uint32 	TimerValueGet (void);


#endif  /* Timer */

/**********************************************************************************************************************
 *  END OF FILE: Timer.h
 *********************************************************************************************************************/
