/********************** (C) COPYRIGHT 2011 STMicroelectronics ********************
  * @file    FanCtrl.h
  * @author  Dedibot
  * @version V1.2.0
  * @date    2016-03-28
  * @brief   风扇控制
*********************************************************************************/
#ifndef FAN_CTRL_H
#define FAN_CTRL_H
#include "de_type.h"

//风扇定义
typedef enum {
	FAN_1,
	FAN_2,
	FAN_3,
	FAN_4,
	FAN_5,
	FAN_6,
	FAN_7,
	FAN_8,
	FAN_9,
	FAN_10,
	FAN_11,
	FAN_12,

	FAN_MAX
}_FAN;

//风扇初始化
extern void FanCtrl_Init(void);
//设置风扇功率
extern void FanCtrl_SetFan(_FAN fan, float percentage);
//风扇控制
extern void FanCtrl_Manage_FAN(void);

#endif
