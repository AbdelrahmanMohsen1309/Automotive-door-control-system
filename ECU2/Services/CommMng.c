#include "CommMng.h"


struct CAN_t can;
CAN_Config CANConfig;

void initSerial(unsigned int protocol)
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

void Send_message(unsigned int protocol,unsigned char* message, unsigned int size)
{
	if (protocol == CAN_PROTOCOL)
	{
		can.CAN_write(&CANConfig, message, size);
	}
}

void Recieve_message(unsigned int protocol,unsigned char* message, unsigned int size)
{
	if (protocol == CAN_PROTOCOL)
	{
		can.CAN_read(&CANConfig, message , size);
	}
}

