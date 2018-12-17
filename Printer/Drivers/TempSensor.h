/********************** (C) COPYRIGHT 2011 STMicroelectronics ********************
  * @file    TempSensor.h
  * @author  Dedibot
  * @version V1.2.0
  * @date    2016-03-28
  * @brief   �¶ȴ��������
*********************************************************************************/
#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
#include "de_type.h"

#define SAMPLE_COUNT		(1<<3)

typedef enum
{
	TEMP_OK,
	TEMP_ERROR_LOW,
	TEMP_ERROR_HIGH
}TEMP_STATUS;


//���ȶ���
typedef enum {
	TEMPSENSOR_1,
	TEMPSENSOR_2,
	TEMPSENSOR_3,
	TEMPSENSOR_4,
	TEMPSENSOR_5,
	TEMPSENSOR_6,
	
	TEMPSENSOR_MAX
}_TEMPSENSOR;

//��ʼ��
extern void TempSensor_Init(void);

extern TEMP_STATUS TempSensor_GetTemperature(_TEMPSENSOR sensor, float *temp);
extern void TempSensor_Timer_5_0(void);

#endif /* TEMPSENSOR_H */

