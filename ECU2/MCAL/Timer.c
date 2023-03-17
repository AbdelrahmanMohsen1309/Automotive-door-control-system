/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Timer.c
 *        \brief  Timer Module
 *
 *      \details  The Driver Configure Timer Module
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Timer.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
CB_type Timer_CALL_BACK_PTR = NULL_PTR;

/**********************************************************************************************************************
 *  Handler Function
 *********************************************************************************************************************/
void Timer_Handler(void){
	if(Timer_CALL_BACK_PTR != NULL_PTR){
		Timer_CALL_BACK_PTR();
	}
}



/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/******************************************************************************
* \Syntax          : void TimerEnable (void)                                      
* \Description     : This function starts the Timer counter. 
*                    If an interrupt handler has been registered, 
*                    it is called when the Timer counter rolls over.                                    
*******************************************************************************/
void 	TimerEnable (void){
	//TODO
}




/******************************************************************************
* \Syntax          : void 	TimerDisable (void)
* \Description     : This function stops the Timer counter. 
*                    If an interrupt handler has been registered, 
*                    it is not called until Timer is restarted.                                    
*******************************************************************************/
void 	TimerDisable (void){
	//TODO
}




/******************************************************************************
* \Syntax          : void 	TimerIntRegister (CB_type pfnHandler)
* \Description     : This function registers the handler to be called 
*                    when a Timer interrupt occurs.                                    
*******************************************************************************/
void 	TimerIntRegister (CB_type pfnHandler){
	if (pfnHandler != NULL_PTR){
		Timer_CALL_BACK_PTR = pfnHandler;
	}else{
		return;
	}
}

/******************************************************************************
* \Syntax          : void 	TimerIntUnregister (void)
* \Description     : This function unregisters the handler to be called 
*                    when a Timer interrupt occurs.                                    
*******************************************************************************/
void 	TimerIntUnregister (void){
  Timer_CALL_BACK_PTR = NULL_PTR;
}


/******************************************************************************
* \Syntax          : void 	TimerIntEnable (void)
* \Description     : This function enables the Timer interrupt, 
*                    allowing it to be reflected to the processor.                                    
*******************************************************************************/
void 	TimerIntEnable (void){
	//TODO
}




/******************************************************************************
* \Syntax          : void 	TimerIntDisable (void)
* \Description     : This function disables the Timer interrupt, 
*                    preventing it from being reflected to the processor.                                    
*******************************************************************************/
void 	TimerIntDisable (void){
	//TODO
}




/******************************************************************************
* \Syntax          : void 	TimerPeriodSet (uint32 ui32Period);
* \Description     : This function sets the rate at which the Timer counter 
*                    wraps, which equates to the number of processor clocks 
*                    between interrupts.                                    
*******************************************************************************/
void 	TimerPeriodSet (uint32 ui32Period){
	//TODO
}






/******************************************************************************
* \Syntax          : uint32 	TimerPeriodGet (void)
* \Description     : This function returns the rate at which the Timer counter 
*                    wraps, which equates to the number of processor clocks 
*                    between interrupts.  
*******************************************************************************/
uint32 	TimerPeriodGet (void){
	//TODO
	return 1;
}






/******************************************************************************
* \Syntax          : uint32 	TimerValueGet (void)
* \Description     : This function returns the current value of the Timer 
*                    counter, which is a value between the period - 1 and zero, 
*                    inclusive.                                    
*******************************************************************************/
uint32 	TimerValueGet (void){
	//TODO
	return 1;
}




/**********************************************************************************************************************
 *  END OF FILE: Timer.c
 *********************************************************************************************************************/
