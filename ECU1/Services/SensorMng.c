#include "SensorMng.h"

struct SensorManager
{
	struct DoorSensor_t DoorSensor;
	struct SpeedSensor_t SpeedSensor;
	struct LightSwitch_t LightSwitch;
};

static struct SensorManager Sensor;


void initSensor(SensorState_t S)
{
	switch(S)
	{
		case Door_Sensor:
		{
			Sensor.DoorSensor.initDoorSensor();
			break;
		}			
		case Light_Switch:
		{
			Sensor.LightSwitch.initLightSwitch();
			break;
		}
		case Speed_Sensor: 
		{
			Sensor.SpeedSensor.initSpeedSensor();
			break;
		}
	}
}

SensorState_t readSensor(SensorState_t S)
{
	SensorState_t value;
	switch(S)
	{
		case Door_Sensor:
		{
			value = Sensor.DoorSensor.getDoorState();
			break;
		}			
		case Light_Switch:
		{
			value = Sensor.LightSwitch.getSwitchState();
			break;
		}
		case Speed_Sensor: 
		{
			value = Sensor.SpeedSensor.getSpeedState();
			break;
		}
	}
	return value;
}
