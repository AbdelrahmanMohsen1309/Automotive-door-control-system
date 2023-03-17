/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SensorMng.h
 *       Module:  Get Updates of Speed Sensor
 *
 *  Description:  header file for Speed Sensor Module    
 *  
 *********************************************************************************************************************/
#include "CAN.h"
#include "Common_Macros.h"

struct CommMng
{
	struct CAN_t CAN; 
};

typedef struct 
{
	void (*initSerial)(unsigned int);
	void (*Send_message)(unsigned int,unsigned char*, unsigned int);
	void (*Recieve_message)(unsigned int,unsigned char*, unsigned int);
}CommunicationManager_t;

typedef unsigned char Protocol_t;

void initSerial(Protocol_t protocol);

void Send_message(Protocol_t protocol,unsigned char* message, unsigned int size);

void Recieve_message(Protocol_t protocol,unsigned char* message, unsigned int size);

