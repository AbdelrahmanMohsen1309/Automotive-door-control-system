/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  CommMng.h
 *       Module:  Communication Manager Module, Service Layer
 *
 *  Description:  header file for Communication Manager Module    
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

void initSerial(unsigned int protocol);

void Send_message(unsigned int protocol,unsigned char* message, unsigned int size);

void Recieve_message(unsigned int protocol,unsigned char* message, unsigned int size);

