/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  OutputControlUnit.c
 *        \Layer  Application Layer
 *
 *      \details  The application code of ECU, which is responsiple of all output devices.
 * 								We have 3 Outputs: Buzzer, Right Light, Left Light.
 * 								We have 1 Tasks that Recieve a periodic status message From CAN Bus of 3 sensors updates.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "OutputControlUnit.h"

/******************************************************************************
 *                                TASKS                                       *
 ******************************************************************************/
//--------------------------------------------------------------
// Task 1: "Task1_getUpdate", {Periodicity: Event Listener}
// This task will receive a periodic message from CAN BUS  
// and update the output states of all output devices depend on 
// received sensor states
//--------------------------------------------------------------
void Task1_getUpdate( void * pvParameters )
{	
		//Create a variable to store received message
		unsigned char *pcRxedChar = NULL;
		
		//Initialize outputs
		
		device.initDevice(Buzzer_device);
		device.initDevice(Lights_device);
	  
	
    //Register a call back function in timer module
		TimerIntRegister(handle_Timer_driver_ISR);
		//Set The period of the Timer 3 Sec
		TimerPeriodSet(3000);
		//Enable The Timer Interrupt
		TimerIntEnable();
	
		for( ;; )
    {
				Serial.Recieve_message(CAN_PROTOCOL,pcRxedChar,sizeof(Device_t));
				/*At first we check that message is not = to NULL*/
				if(*pcRxedChar != NULL)
				{
					/*Then we unblock the received message to know which sensor is sending*/
					if ((*pcRxedChar & SensorTypeMasking) == DoorSensorMasking)
					{
						//Update the Door Sensor Value
						(*pcRxedChar & SensorValueMasking)?(DoorState = Door_is_close):(DoorState = Door_is_open);
					}
					else if ((*pcRxedChar & SensorTypeMasking) == LightSwitchMasking)
					{
						//Update the Light Switch Value
						(*pcRxedChar & SensorValueMasking)?(LightSwitchState = Light_switch_pressed):(LightSwitchState = Light_switch_unpressed);
					}
					else if ((*pcRxedChar & SensorTypeMasking) == SpeedSensorMasking)
					{
						//Update the Speed Sensor Value
						(*pcRxedChar & SensorValueMasking)?(Speedstate = Car_is_moving):(Speedstate = Car_is_stopped);
					}
				}
				*pcRxedChar = NULL;
				
				//CASE1
				if((DoorState == Door_is_open) && (Speedstate == Car_is_moving))
					{
						device.writeOutput(Buzzer_device, Buzzer_On);
						device.writeOutput(Lights_device, Lights_Off);
					}
				//CASE2
					
				else if((DoorState == Door_is_open) && (Speedstate == Car_is_stopped))
				{
						device.writeOutput(Buzzer_device, Buzzer_Off);
						device.writeOutput(Lights_device, Lights_On);
				}
				//CASE3
				
				else if((DoorState == Door_is_close) && (device.readOutput(Lights_device) == PIN_IS_HIGH))
				{
						//Lights turn off after 3 sec
						TimerEnable();
				}
				//CASE4
				
				else if((Speedstate == Car_is_moving) && (LightSwitchState == Light_switch_pressed))
				{
						device.writeOutput(Buzzer_device, Buzzer_Off);
						device.writeOutput(Lights_device, Lights_On);
				}
				//CASE5
				
				else if((Speedstate == Car_is_stopped) && (LightSwitchState == Light_switch_pressed))
				{
						device.writeOutput(Buzzer_device, Buzzer_On);
						device.writeOutput(Lights_device, Lights_On);
				}
    }
}

/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();

	/* Now all the tasks have been started - start the scheduler.*/
	xTaskCreate(
                    Task1_getUpdate,       /* Function that implements the task. */
                    "Update Message",          /* Text name for the task. */
                    100,             /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    Task_periority,/* Priority at which the task is created. */
                    &xTaskHandle1_Update );      /* Used to pass out the created task's handle. */
	
	
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/

/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */
	
	Serial.initSerial(CAN_PROTOCOL);
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/

void handle_Timer_driver_ISR(void)
{
	device.writeOutput(Lights_device, Lights_Off);
	TimerDisable();
}
