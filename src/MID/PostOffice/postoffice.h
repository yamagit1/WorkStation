/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

#ifndef __POSTOFFICE_H__
#define __POSTOFFICE_H__

#include "header.h"
#include "task.h"
#include "queue.h"

#define MAX_NUMBER_TASK_REGISTER  	10
#define MAX_DELAY_RECEIVER_MSG		10
#define MAX_DELAY_SEND_MSG			10


typedef struct
{
	__uint32 msgID;
	TaskHandle_t pidTaskSource;
	TaskHandle_t pidTaskDestination;
	__uint32 timeSend;
	__uint32 keyMsg;

}__S_Msg_signal;

typedef struct
{
	TaskHandle_t	pidTask;
	xQueueHandle	queueReceiveTask;
}__S_Task_Register;

extern xQueueHandle gPostOfficeAddress;
extern __S_Task_Register gPostOfficeRegister[MAX_NUMBER_TASK_REGISTER];
extern __uint32 gNumberTaskRegister;

__E_Bollen PO_sendBackMsg();
void PO_init();
void PO_taskRegister();
void PO_reciverMSG();


#endif /* __POSTOFFICE_H__ */
