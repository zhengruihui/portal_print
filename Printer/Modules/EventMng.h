/********************** (C) COPYRIGHT 2015 DediBot ******************************
  * @file    EventMng.h
  * @author  Dedibot
  * @version V1.2.0
  * @date    2017-05-25
  * @brief   事件管理
*********************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EVNETMNG_H
#define EVNETMNG_H

#include "stm32f4xx.h"
#include "de_type.h"

typedef enum 
{
	/* 外部信号事件 */
	/* 按键、门、缺料等 */
	
	
	/* 通信事件 */
	PRINTER_EVENT_NULL, 						//空，无意义
	PRINTER_EVENT_STANDBY,						//待机
	PRINTER_EVENT_PRINT,						//打印
	PRINTER_EVENT_PAUSE,
	PRINTER_EVENT_CONTINUE,
	PRINTER_EVENT_CONTROL,						//控制,执行Gcode
	
	PRINTER_EVENT_READCONFIG,					//读入配置文件
	PRINTER_EVENT_SW_FRAME,						//切换龙门架
	PRINTER_EVENT_STARTFRAME,					//选中的龙门架开始打印
	PRINTER_EVENT_STOPFRAME,					//选中的龙门架停止打印
	PRINTER_EVENT_STOP_FRAME3_Y,				//第三个龙门架的选中的Y轴结束打印

	
	/* 内部事件 */
	PRINTER_EVENT_SETWAITTEMP,


	
	PRINTER_EVENT_MAX
	
}EVENT_NAME;


typedef void (*EVENT_NOTIFY)(u8);
typedef struct {
	EVENT_NAME event;
	EVENT_NOTIFY notify;
}EVENT;

typedef enum
{
	/* 等级0为最高 */
	EVENT_LEVEL_0,
	EVENT_LEVEL_1,
	EVENT_LEVEL_2,
	EVENT_LEVEL_3,
	EVENT_LEVEL_NORMAL = EVENT_LEVEL_3,
	
	EVENT_LEVEL_MAX
}EVENT_LEVEL;



extern void EventMng_SetEvent_Normal(EVENT_NAME e, EVENT_NOTIFY notify);
extern void EventMng_SetEvent_Level(EVENT_NAME e, EVENT_NOTIFY notify, EVENT_LEVEL level);
extern bool EventMng_GetEvent(EVENT *event);
extern void EventMng_Init(void);

#endif  //EVNETMNG_H
