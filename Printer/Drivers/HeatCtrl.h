/********************** (C) COPYRIGHT 2011 STMicroelectronics ********************
  * @file    HeatCtrl.h
  * @author  Dedibot
  * @version V1.2.0
  * @date    2016-03-28
  * @brief   加热驱动
*********************************************************************************/
#ifndef HEATCTRL_H
#define HEATCTRL_H
#include "de_type.h"

//风扇定义
typedef enum {
	HEATER_1,	//J17
	HEATER_2,	//J18
	HEATER_3,	//J19
	HEATER_4,	//J20
	HEATER_5,	//J25
	HEATER_6,	//J26

	HEATER_MAX
}_HEATER;

//初始化
extern void HeatCtrl_Init(void);

extern void HeatCtrl_On(_HEATER heater);
extern void HeatCtrl_Off(_HEATER heater);

#endif /* HEATCTRL_H */


