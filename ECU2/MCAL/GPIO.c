#include <stdint.h>
#include "Common_Macros.h"
#include "GPIO.h"
#include "lpc21xx.h"


void GPIO_init(portX_t PortName, pinX_t pinNum, pinDir_t mode)
{
		switch(PortName)
		{
			case PORT_0:
				(mode == INPUT)?(CLR_BIT(IODIR0, pinNum)):(SET_BIT(IODIR0, pinNum));
				break;
	
			case PORT_1:
				(mode == INPUT)?(CLR_BIT(IODIR1, pinNum)):(SET_BIT(IODIR1, pinNum));
				break;
		}
}



pinState_t GPIO_readPin(portX_t PortName, pinX_t pinNum)
{
	pinState_t state;
	
	switch(PortName)
	{
		case PORT_0:
			{
				state = (pinState_t) GET_BIT(IOPIN0, pinNum);
				break;
			}

		case PORT_1:
			{
				state = (pinState_t) GET_BIT(IOPIN1, pinNum);
				break;
			}
	}
	
	return state;
}


void GPIO_writePin(portX_t portName, pinX_t pinNum, pinState_t pinState)
{
	switch(portName)
	{
		case PORT_0:
			if(PIN_IS_LOW == pinState)
			{
				SET_BIT(IOCLR0, pinNum);
			}
			else if (PIN_IS_HIGH == pinState)
			{
				SET_BIT(IOSET0, pinNum);
			}
			else
			{
				
			}
			break;

		case PORT_1:
			if(PIN_IS_LOW == pinState)
			{
				SET_BIT(IOCLR1, pinNum);
			}
			else if (PIN_IS_HIGH == pinState)
			{
				SET_BIT(IOSET1, pinNum);
			}
			else
			{
				
			}
	}
}

registerState_t GPIO_readRegister(portX_t portName){	
	registerState_t registerState;
	switch(portName)
	{
		case PORT_0:
			{
				registerState = IOPIN0;
				break;
			}

		case PORT_1:
			{
				registerState = IOPIN1;
				break;
			}
	}
	return registerState;
}
void GPIO_writeRegister(portX_t portName, registerState_t registerState){
	switch(portName)
	{
		case PORT_0:
				IOCLR0 = ~registerState;
				IOSET0 = registerState;
				break;

		case PORT_1:
				IOCLR1 = ~registerState;
				IOSET1 = registerState;
				break;
	}
}
