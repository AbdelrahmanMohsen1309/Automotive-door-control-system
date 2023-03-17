/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"
#include "queue.h"
/* Peripheral includes. */
#include "ExtDvsMng.h"
#include "CommMng.h"
#include "Timer.h"


/**********************************************************************************************************************
 *  Global Variables
 *********************************************************************************************************************/
DevicesManager_t device;
CommunicationManager_t Serial;
/**********************************************************************************************************************
 *  Global Enumurations and Structures (Configuration Options)
 *********************************************************************************************************************/
/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
#define Task_periority ( ( UBaseType_t ) 1U )

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )

#define SensorValueMasking 0x01
#define SensorTypeMasking  0xF0
#define DoorSensorMasking  0x10
#define LightSwitchMasking 0x20
#define SpeedSensorMasking 0x40

typedef unsigned char DoorState_t;
DoorState_t DoorState = 0xFF;
enum{
	Door_is_open , Door_is_close
}Door;

typedef unsigned char SpeedState_t;
SpeedState_t Speedstate = 0xFF;
enum{
	Car_is_stopped , Car_is_moving
}Speed;

typedef unsigned char LightSwitchState_t;
LightSwitchState_t LightSwitchState = 0xFF;
enum{
	Light_switch_unpressed , Light_switch_pressed
}Switch;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static void prvSetupHardware( void );
void handle_Timer_driver_ISR(void);

/******************************************************************************
 *                            TASKS HANDLERS                                  *
 ******************************************************************************/
TaskHandle_t xTaskHandle1_Update  = NULL;
