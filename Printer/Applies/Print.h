/********************** (C) COPYRIGHT 2011 STMicroelectronics ********************
  * @file    My_SdCard.h
  * @author  Dedibot
  * @version V1.2.0
  * @date    2016-03-25
  * @brief   打印操作
*********************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PRINT_H
#define __PRINT_H
#include "de_type.h"
#include "EventMng.h"
#include "configuration.h"
#include "portalframe.h"


/*******************************************
	输出接口
********************************************/
extern void Print_Pro( PORTALFRAME *this );
extern void Print_Stop( PORTALFRAME *this );
extern bool Print_Start( PORTALFRAME *this );
extern void Print_Pause( PORTALFRAME *this );
extern void Print_Continue( PORTALFRAME *this );
extern void Print_Finish( PORTALFRAME *this );
extern void Print_Exit( PORTALFRAME *this );
extern void Print_Init( PORTALFRAME *this );
extern void Print_EventAction( PORTALFRAME *this, EVENT event );
#endif  //__PRINT_H



