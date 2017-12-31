/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

#include "header.h"

extern __INT16 gCurrentTemperatureC;
extern __UINT16 gCurrentTemperatureF;

void TEM_initialize(void);
void TEM_updateTemperature(void);

#endif /* __TEMPERATURE_H_ */
