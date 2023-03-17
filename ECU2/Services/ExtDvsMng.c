#include "ExtDvsMng.h"

struct ExternalDevicesManager
{
	struct Buzzer_t Buzzer;
	struct Lights_t Lights;
	
};

static struct ExternalDevicesManager device;


void initDevice(Device_t Device)
{
	switch(Device)
	{
		case Buzzer_device:
		{
			device.Buzzer.initBuzzer();
			break;
		}			
		case Lights_device:
		{
			device.Lights.initLights();
			break;
		}
	}
}

void writeOutput(Device_t Device, Device_t DeviceState)
{
	switch(Device)
	{
		case Buzzer_device:
		{
			device.Buzzer.setBuzzerState(DeviceState);
			break;
		}			
		case Lights_device:
		{
			device.Lights.setLightState(DeviceState);
			break;
		}
	}
}

Device_t readOutput(Device_t Device)
{
	Device_t D;
	switch(Device)
	{
		case Buzzer_device:
		{
			D = device.Buzzer.getBuzzerState();
			break;
		}			
		case Lights_device:
		{
			D = device.Lights.getLightState();
			break;
		}
	}
	return D;
}
