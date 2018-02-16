/*
 * signal.c
 *
 *  Created on: Dec 26, 2017
 *      Author: yama
 */

#include "signal.h"
#include "postoffice.h"
#include "queue.h"

void SIG_init()
{

}

void SIG_createSignal(TaskHandle_t pidTaskDes, __uint32 key)
{
	__S_Msg_signal msg;

	msg.keyMsg = key;
	msg.msgID = 0;
	msg.pidTaskDestination = pidTaskDes;
	msg.pidTaskSource = 0;
	msg.timeSend = 0;

	xQueueOverwrite(gPostOfficeAddress, &msg);

}
