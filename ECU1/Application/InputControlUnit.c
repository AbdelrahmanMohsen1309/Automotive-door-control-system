/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  InputControlUnit.c
 *        \Layer  Application Layer
 *
 *      \details  The application code of ECU, which is responsiple of all input devices.
 * 								We have 3 sensors: Door, Speed, Light Switch.
 * 								We have 3 Tasks that send a periodic status message to CAN Bus of 3 sensors updates.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "InputControlUnit.h"

/******************************************************************************
 *                                TASKS                                       *
 ******************************************************************************/
//------------------------------------------------------------------------------
// Task 1: "Task1_DoorState", {Periodicity: 10mS}
// This task will monitor Door Sensor and send status Message every 10mS
// On CAN Bus to ECU 2 
//------------------------------------------------------------------------------
void Task1_DoorState( void * pvParameters )
{
		
		TickType_t         xLastWakeTime = 0;
		const TickType_t   xFrequency    = doorTaskDelay;
		SensorState_t      doorState;
	  PtrToSensorState_t ptr           = &doorState;
	
	  Sensor.initSensor(Door_Sensor);
	
    for( ;; )
    {
				/*Get Sensor Updates*/
				doorState = DoorSensorMasking | Sensor.readSensor(Door_Sensor);
			
        /* Send Data on CAN Bus */
				Serial.Send_message(CAN_PROTOCOL, ptr, sizeof(SensorState_t));
			
				/*Wait 5 mS and repeat*/
				vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}

//------------------------------------------------------------------------------
// Task 2: "Task1_LightSwitch", {Periodicity: 20mS}
// This task will monitor Light Switch and send status Message every 10mS
// On CAN Bus to ECU 2 
//------------------------------------------------------------------------------
void Task2_LightSwitch( void * pvParameters )
{
    TickType_t         xLastWakeTime     = 0;
		const TickType_t   xFrequency        = LightSwitchTaskDelay;
		SensorState_t      LightSwitchState;
		PtrToSensorState_t ptr               = &LightSwitchState;
	
		Sensor.initSensor(Light_Switch);
    for( ;; )
    {
				/*Get Sensor Updates*/
				LightSwitchState = LightSwitchMasking | Sensor.readSensor(Light_Switch);
        
			  /* Send Data on CAN Bus */
				Serial.Send_message(CAN_PROTOCOL, ptr, sizeof(SensorState_t));
				
			  /*Wait 5 mS and repeat*/
				vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}

//------------------------------------------------------------------------------
// Task 3: "Task1_SpeedState", {Periodicity: 5mS}
// This task will monitor Speed Sensor and send status Message every 10mS
// On CAN Bus to ECU 2 
//------------------------------------------------------------------------------
void Task3_SpeedState( void * pvParameters )
{
    TickType_t         xLastWakeTime = 0;
		const TickType_t   xFrequency    = SpeedTaskDelay;
		SensorState_t      SpeedState;
		PtrToSensorState_t ptr           = &SpeedState;
	
		Sensor.initSensor(Speed_Sensor);
    
	  for( ;; )
    {
				/*Get Sensor Updates*/
				SpeedState = SpeedSensorMasking | Sensor.readSensor(Speed_Sensor);
         
			  /* Send Data on CAN Bus */
				Serial.Send_message(CAN_PROTOCOL, ptr, sizeof(SensorState_t));
				
			  /*Wait 5 mS and repeat*/
				vTaskDelayUntil( &xLastWakeTime, xFrequency );
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
                    Task1_DoorState,       /* Function that implements the task. */
                    "Door Sensor",          /* Text name for the task. */
                    100,             /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    Task_periority,/* Priority at which the task is created. */
                    &xTaskHandle1_Door );      /* Used to pass out the created task's handle. */
	
	xTaskCreate(
                    Task2_LightSwitch,       /* Function that implements the task. */
                    "Light Switch",          /* Text name for the task. */
                    100,             /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    Task_periority,/* Priority at which the task is created. */
                    &xTaskHandle2_LightSwitch );      /* Used to pass out the created task's handle. */
	
	xTaskCreate(
                    Task3_SpeedState,       /* Function that implements the task. */
                    "Speed Sensor",          /* Text name for the task. */
                    100,             /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    Task_periority,/* Priority at which the task is created. */
                    &xTaskHandle3_Speed );      /* Used to pass out the created task's handle. */
	
	
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/



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


