/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

#ifndef SRC_MID_SIGNAL_SIGNAL_H_
#define SRC_MID_SIGNAL_SIGNAL_H_
#include "header.h"
#include "task.h"


void SIG_init();
void SIG_createSignal(TaskHandle_t pidTaskDes, __UINT32 key);

#endif /* SRC_MID_SIGNAL_SIGNAL_H_ */
