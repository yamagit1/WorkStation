/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

#include "postoffice.h"



xQueueHandle gPostOfficeAddress;
__S_Task_Register gPostOfficeRegister[MAX_NUMBER_TASK_REGISTER];
__UINT32 gNumberTaskRegister;

__E_Bollen PO_sendBackMsg()
{
	__S_Msg_signal msgReceived;
	__UINT32 i;

	if (xQueuePeek(gPostOfficeAddress, &msgReceived, MAX_DELAY_RECEIVER_MSG))
	{
		for (i = 0; i < gNumberTaskRegister; i++)
		{
			if (msgReceived.pidTaskDestination == NULL)
			{
				xQueueOverwrite(gPostOfficeRegister[i].queueReceiveTask, &msgReceived);
			}
			else if (msgReceived.pidTaskDestination == gPostOfficeRegister[i].pidTask)
			{
				xQueueOverwrite(gPostOfficeRegister[i].queueReceiveTask, &msgReceived);

				break;
			}
		}

	}
	else
	{
		return eFALSE;
	}

	return eTRUE;
}


void PO_init()
{
	gPostOfficeAddress = xQueueCreate(20, sizeof(__S_Msg_signal));

	gNumberTaskRegister = 0;
}


void PO_taskRegister()
{

}

void PO_reciverMSG()
{

}

