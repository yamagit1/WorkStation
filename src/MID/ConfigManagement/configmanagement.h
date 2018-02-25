/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

#ifndef __CONFIGMANAGEMENT_H__
#define __CONFIGMANAGEMENT_H__

#include "header.h"

void CM_taskMonitorHandler(void *p_parameters);
void CM_taskCountTime(void *p_parameters);
void CM_taskUpdateTemperature(void *p_parameters);
void CM_taskBinlkLed();
void CM_taksTime(void *p_parameters);
void CM_taskNetwork(void *p_parameters);

#endif /* SRC_MID_CONFIGMANAGEMENT_CONFIGMANAGEMENT_H_ */
