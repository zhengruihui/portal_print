/********************** (C) COPYRIGHT 2015 DediBot ******************************
  * @file    EventMng.h
  * @author  Dedibot
  * @version V1.2.0
  * @date    2017-05-25
  * @brief   �¼�����
*********************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EVNETMNG_H
#define EVNETMNG_H

#include "stm32f4xx.h"
#include "de_type.h"

typedef enum 
{
	/* �ⲿ�ź��¼� */
	/* �������š�ȱ�ϵ� */
	
	
	/* ͨ���¼� */
	PRINTER_EVENT_NULL, 						//�գ�������
	PRINTER_EVENT_STANDBY,						//����
	PRINTER_EVENT_PRINT,						//��ӡ
	PRINTER_EVENT_PAUSE,
	PRINTER_EVENT_CONTINUE,
	PRINTER_EVENT_CONTROL,						//����,ִ��Gcode
	
	PRINTER_EVENT_READCONFIG,					//���������ļ�
	PRINTER_EVENT_SW_FRAME,						//�л����ż�
	PRINTER_EVENT_STARTFRAME,					//ѡ�е����żܿ�ʼ��ӡ
	PRINTER_EVENT_STOPFRAME,					//ѡ�е����ż�ֹͣ��ӡ
	PRINTER_EVENT_STOP_FRAME3_Y,				//���������żܵ�ѡ�е�Y�������ӡ

	
	/* �ڲ��¼� */
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
	/* �ȼ�0Ϊ��� */
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