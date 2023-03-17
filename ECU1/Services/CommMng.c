#include "CommMng.h"


struct CAN_t can;
CAN_Config CANConfig;

void initSerial(Protocol_t protocol)
{
	if(protocol == CAN_PROTOCOL)
	{
		/*
			Set CAN configurations
			CANConfig. x = y;
		*/
		can.CAN_init();
		
	}
}

void Send_message(Protocol_t protocol,unsigned char* message, unsigned int size)
{
	if (protocol == CAN_PROTOCOL)
	{
		can.CAN_write(&CANConfig, message, size);
	}
}

void Recieve_message(Protocol_t protocol,unsigned char* message, unsigned int size)
{
	if (protocol == CAN_PROTOCOL)
	{
		can.CAN_read(&CANConfig, message , size);
	}
}

