/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SensorMng.h
 *       Module:  Get Updates of Speed Sensor
 *
 *  Description:  header file for Speed Sensor Module    
 *  
 *********************************************************************************************************************/
#include "DoorSensor.h"
#include "SpeedSensor.h"
#include "LightSwitch.h"

#define Door_Sensor  1
#define Light_Switch 2
#define Speed_Sensor 3

typedef unsigned char   SensorState_t;
typedef unsigned char * PtrToSensorState_t;

typedef struct 
{
	void (*initSensor)(SensorState_t);
	SensorState_t (*readSensor)(SensorState_t);
}SensorManager_t;

void initSensor(SensorState_t S);
SensorState_t readSensor(SensorState_t S);
