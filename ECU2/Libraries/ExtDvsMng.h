/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ExtDvsMng.h
 *       Module:  Get Updates of Speed Sensor
 *
 *  Description:  header file for Speed Sensor Module    
 *  
 *********************************************************************************************************************/
#include "Lights.h"
#include "Buzzer.h"


#define Buzzer_device 1
#define Lights_device  2


typedef unsigned char   Device_t;
typedef unsigned char * PtrToDeviceState_t;

typedef struct 
{
	void (*initDevice)(Device_t);
	void (*writeOutput)(Device_t, Device_t);
	Device_t (*readOutput)(Device_t Device);
}DevicesManager_t;

void initDevice(Device_t D);
void writeOutput(Device_t Device, Device_t DeviceState);

