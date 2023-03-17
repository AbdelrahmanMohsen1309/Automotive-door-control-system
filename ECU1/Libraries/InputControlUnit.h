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
#include "SensorMng.h"
#include "CommMng.h"

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


#define DoorSensorMasking  0x10
#define LightSwitchMasking 0x20
#define SpeedSensorMasking 0x40

#define doorTaskDelay        10
#define LightSwitchTaskDelay 20
#define SpeedTaskDelay       5

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static void prvSetupHardware( void );

/**********************************************************************************************************************
 *  Global Variables
 *********************************************************************************************************************/
SensorManager_t Sensor;
CommunicationManager_t Serial;
/******************************************************************************
 *                            TASKS HANDLERS                                  *
 ******************************************************************************/
TaskHandle_t xTaskHandle1_Door        = NULL;
TaskHandle_t xTaskHandle2_LightSwitch = NULL;
TaskHandle_t xTaskHandle3_Speed       = NULL;
