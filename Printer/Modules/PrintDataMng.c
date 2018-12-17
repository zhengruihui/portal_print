#include "PrintDataMng.h"
#include "Configuration.h"
#include "ErrorMng.h"
#include "string.h"
#include "macros.h"


#define LOCALREAD_SIZE		(512)

static char m_TempReadBuffer[LOCALREAD_SIZE];

/*******************************************************************
���ܣ��ж϶����Ƿ�Ϊ��
�����ߣ�liu-cy
�������ڣ�2016/10/24
������
����ֵ�� 
********************************************************************/
bool PrintDataMng_QueueIsFull(PRINTDATAMNG *this) 
{  
	bool ret;
	if(QUEUE_PacketLengthGet(&this->printDataQueue) == (PRINT_DATA_BUF_SIZE - 1))
	{
		ret = True;
	}
	else ret = False;
  return ret;
}
/*******************************************************************
���ܣ���ȡ�����������ֽ�
�����ߣ�liu-cy
�������ڣ�2016/12/22
������
����ֵ�� �����п��õ��ֽ�
********************************************************************/
uint32_t PrintDataMng_GetQueueSize(PRINTDATAMNG *this)
{
	return QUEUE_PacketLengthGet(&this->printDataQueue);
}
/*******************************************************************
���ܣ���ȡ���п����ֽ�
�����ߣ�liu-cy
�������ڣ�2016/10/24
������
����ֵ�� �����п��õ��ֽ�
********************************************************************/
u16 PrintDataMng_GetQueueAvalilableSize(PRINTDATAMNG *this)
{
	return (PRINT_DATA_BUF_SIZE-1 - QUEUE_PacketLengthGet(&this->printDataQueue));
}

/*******************************************************************
���ܣ���ȡһ��Gcode
�����ߣ�liu-cy
�������ڣ�2016/10/24
������
	r_data:����
	length:���ݳ���
����ֵ:SD������״̬
********************************************************************/ 
bool PrintDataMng_GetOneLine( PRINTDATAMNG *this, char *r_data, u8* length )
{
	bool ret;
	if(this->printByteSkip_Count > 0)
	{
		QUEUE_PacketMove(&this->printDataQueue, this->printByteSkip_Count);
		this->printByteSkip_Count = 0;
	}
	(*length) = QUEUE_PacketCharSplit(&this->printDataQueue, '\n', (u8 *)r_data, PRINT_DATA_BUF_SIZE);
	if( (*length)== 0)
	{
		ret = False;
	}
	else 
	{
		ret = True;
	}	
	return ret;
}

/*******************************************************************
���ܣ���ӡ���������
�����ߣ�pang-wei
�������ڣ�2017/5/27
������
buf����  len����
����ֵ����
********************************************************************/
void PrintDataMng_ReceDataToQueue(PRINTDATAMNG *this, char* buf ,u16 len)
{
	if(this->dataSourceType != DATASOURCE_LOCAL)
	{
		QUEUE_PacketIn(&this->printDataQueue, (u8 *)buf,len);
	}
}
/*******************************************************************
���ܣ�������ӡ���ݶ���
�����ߣ�pang-wei
�������ڣ�2017/5/27
������
buf����  len����
����ֵ����
********************************************************************/
void PrintDataMng_CreatQueue(PRINTDATAMNG *this)
{
	memset(this->printDataBuf ,0 ,sizeof(this->printDataBuf));
	QUEUE_PacketCreate(&this->printDataQueue, this->printDataBuf, sizeof(this->printDataBuf));
}
/******************************************
���ܣ��ָ�����������
�����ߣ�
�������ڣ�
��������
����ֵ����
*******************************************/
void PrintDataMng_RecoverRxIndex( PRINTDATAMNG *this, uint32_t value )
{
	this->printData_RxIndex = 0;
}
/******************************************
���ܣ���ȡ��������ȡ����
�����ߣ�
�������ڣ�
��������
����ֵ����
*******************************************/
uint32_t PrintDataMng_GetRxIndex( PRINTDATAMNG *this )
{
	return this->printData_RxIndex;
}
/******************************************
���ܣ���ȡ��������ȡ����
�����ߣ�
�������ڣ�
��������
����ֵ����
*******************************************/
void PrintDataMng_SetSkipByte(PRINTDATAMNG *this, u32 count)
{
	this->printByteSkip_Count = count;
}
/******************************************
���ܣ���ʱ��û�д�ӡ�����ж�
�����ߣ�
�������ڣ�
��������
����ֵ����
*******************************************/
void PrintDataMng_NoPrintDataCheck(PRINTDATAMNG *this)
{
//	if(IsErrorFlag(ERROR_NOPRINTDATA) == True)
//	{
//		return;
//	}
	// if((PrintDataMng_GetQueueAvalilableSize() < ONEPARME_DATA_SIZE))
	// {
		// m_QueueEmptyTime = HAL_GetTick();
	// }
	// else if((HAL_GetTick() - m_QueueEmptyTime) > QUEUEEMPTY_TIME)
	// {
// //		ErrorMng_SetError(ERROR_NOPRINTDATA);
	// }
}

/*******************************************************************
���ܣ���ӡ���ݳ�ʼ��
�����ߣ�pang-wei
�������ڣ�2017/5/27
������
buf����  len����
����ֵ����
********************************************************************/
void PrintDataMng_SetDataSource(PRINTDATAMNG *this, DATASOURCE_TYPE type)
{	
	this->dataSourceType = type;
}

/*******************************************************************
���ܣ���ӡ���ݳ�ʼ��
�����ߣ�pang-wei
�������ڣ�2017/5/27
������
buf����  len����
����ֵ����
********************************************************************/
void PrintDataMng_SetDataFileName(PRINTDATAMNG *this, char *filename)
{	
	this->filename = filename;
}


/*******************************************************************
���ܣ���ӡ���ݳ�ʼ��
�����ߣ�pang-wei
�������ڣ�2017/5/27
������
buf����  len����
����ֵ����
********************************************************************/
bool PrintDataMng_LocalStart(PRINTDATAMNG *this)
{	
	static u8 res;
	
	// DISABLE_TIMER_INT
	res = FATFS_OpenFile(&this->prtFile, this->filename, FA_READ);
	// ENABLE_TIMER_INT
	
	if(res == FR_OK)
	{
		Logger_string("open gcode file successfully.\n");
		
		PrintDataMng_DataClear(this);
		
		this->isLocalStart = True;
		this->diskErrCount = 0;
		this->intErrCount = 0;
		
		this->totalReadSize = 0;
		
		return True;
	}
	else
	{
		Logger_string("open gcode file failed.\n");
	}
	FATFS_CloseFile(&this->prtFile);
	return False;
}

u32 PrintDataMng_GetTotalSize(PRINTDATAMNG *this)
{
	return FATFS_GetFileSize(&this->prtFile);
}

/*******************************************************************
���ܣ���ӡ���ݳ�ʼ��
�����ߣ�pang-wei
�������ڣ�2017/5/27
������
buf����  len����
����ֵ����
********************************************************************/
void PrintDataMng_Init(PRINTDATAMNG *this)
{
	this->dataSourceType = DATASOURCE_COM;
	this->printDataFarme = 0;
	this->queueEmptyTime = HAL_GetTick();
	this->isLocalStart = False;
	PrintDataMng_DataClear(this);
}

/*******************************************************************
���ܣ������ӡ����
�����ߣ�
�������ڣ�
������
����ֵ����
********************************************************************/
void PrintDataMng_DataClear(PRINTDATAMNG *this)
{
	PrintDataMng_CreatQueue(this);
}

/*******************************************************************
���ܣ���ӡ����ֹͣ
�����ߣ�pang-wei
�������ڣ�2017/5/27
������
����ֵ����
********************************************************************/
void PrintDataMng_Stop(PRINTDATAMNG *this)
{
	this->dataSourceType = DATASOURCE_COM;
	this->isLocalStart = False;
	PrintDataMng_DataClear(this);
	
	FATFS_CloseFile(&this->prtFile);
}

/*******************************************************************
���ܣ�
�����ߣ�
�������ڣ�2017/5/27
������
����ֵ����
********************************************************************/
void PrintDataMng_Pro(PRINTDATAMNG *this)
{
	u8 res = 0;
	u32 readLen = 0;
	if((this->isLocalStart) && (this->dataSourceType == DATASOURCE_LOCAL))
	{
		if(PrintDataMng_GetQueueAvalilableSize(this) >= LOCALREAD_SIZE)
		{
			res = FATFS_ReadFile(&this->prtFile, m_TempReadBuffer, LOCALREAD_SIZE, &readLen);		
			if(res == FR_OK)
			{
				this->totalReadSize += readLen;
				QUEUE_PacketIn(&this->printDataQueue, (u8 *)m_TempReadBuffer, readLen);
			}
			else
			{
				this->prtFile.err = 0;
				this->diskErrCount++;
			}
		}
	}
}




