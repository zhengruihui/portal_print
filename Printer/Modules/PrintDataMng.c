#include "PrintDataMng.h"
#include "Configuration.h"
#include "ErrorMng.h"
#include "string.h"
#include "macros.h"


#define LOCALREAD_SIZE		(512)

static char m_TempReadBuffer[LOCALREAD_SIZE];

/*******************************************************************
功能：判断队列是否为满
作成者：liu-cy
作成日期：2016/10/24
参数：
返回值： 
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
功能：获取队列中已用字节
作成者：liu-cy
作成日期：2016/12/22
参数：
返回值： 队列中可用的字节
********************************************************************/
uint32_t PrintDataMng_GetQueueSize(PRINTDATAMNG *this)
{
	return QUEUE_PacketLengthGet(&this->printDataQueue);
}
/*******************************************************************
功能：获取队列可用字节
作成者：liu-cy
作成日期：2016/10/24
参数：
返回值： 队列中可用的字节
********************************************************************/
u16 PrintDataMng_GetQueueAvalilableSize(PRINTDATAMNG *this)
{
	return (PRINT_DATA_BUF_SIZE-1 - QUEUE_PacketLengthGet(&this->printDataQueue));
}

/*******************************************************************
功能：获取一行Gcode
作成者：liu-cy
作成日期：2016/10/24
参数：
	r_data:数据
	length:数据长度
返回值:SD卡操作状态
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
功能：打印数据入队列
作成者：pang-wei
作成日期：2017/5/27
参数：
buf数据  len长度
返回值：无
********************************************************************/
void PrintDataMng_ReceDataToQueue(PRINTDATAMNG *this, char* buf ,u16 len)
{
	if(this->dataSourceType != DATASOURCE_LOCAL)
	{
		QUEUE_PacketIn(&this->printDataQueue, (u8 *)buf,len);
	}
}
/*******************************************************************
功能：创建打印数据队列
作成者：pang-wei
作成日期：2017/5/27
参数：
buf数据  len长度
返回值：无
********************************************************************/
void PrintDataMng_CreatQueue(PRINTDATAMNG *this)
{
	memset(this->printDataBuf ,0 ,sizeof(this->printDataBuf));
	QUEUE_PacketCreate(&this->printDataQueue, this->printDataBuf, sizeof(this->printDataBuf));
}
/******************************************
功能：恢复缓冲区索引
作成者：
作成日期：
参数：无
返回值：无
*******************************************/
void PrintDataMng_RecoverRxIndex( PRINTDATAMNG *this, uint32_t value )
{
	this->printData_RxIndex = 0;
}
/******************************************
功能：获取缓冲区读取索引
作成者：
作成日期：
参数：无
返回值：无
*******************************************/
uint32_t PrintDataMng_GetRxIndex( PRINTDATAMNG *this )
{
	return this->printData_RxIndex;
}
/******************************************
功能：获取缓冲区读取索引
作成者：
作成日期：
参数：无
返回值：无
*******************************************/
void PrintDataMng_SetSkipByte(PRINTDATAMNG *this, u32 count)
{
	this->printByteSkip_Count = count;
}
/******************************************
功能：长时间没有打印数据判断
作成者：
作成日期：
参数：无
返回值：无
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
功能：打印数据初始化
作成者：pang-wei
作成日期：2017/5/27
参数：
buf数据  len长度
返回值：无
********************************************************************/
void PrintDataMng_SetDataSource(PRINTDATAMNG *this, DATASOURCE_TYPE type)
{	
	this->dataSourceType = type;
}

/*******************************************************************
功能：打印数据初始化
作成者：pang-wei
作成日期：2017/5/27
参数：
buf数据  len长度
返回值：无
********************************************************************/
void PrintDataMng_SetDataFileName(PRINTDATAMNG *this, char *filename)
{	
	this->filename = filename;
}


/*******************************************************************
功能：打印数据初始化
作成者：pang-wei
作成日期：2017/5/27
参数：
buf数据  len长度
返回值：无
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
功能：打印数据初始化
作成者：pang-wei
作成日期：2017/5/27
参数：
buf数据  len长度
返回值：无
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
功能：清除打印数据
作成者：
作成日期：
参数：
返回值：无
********************************************************************/
void PrintDataMng_DataClear(PRINTDATAMNG *this)
{
	PrintDataMng_CreatQueue(this);
}

/*******************************************************************
功能：打印数据停止
作成者：pang-wei
作成日期：2017/5/27
参数：
返回值：无
********************************************************************/
void PrintDataMng_Stop(PRINTDATAMNG *this)
{
	this->dataSourceType = DATASOURCE_COM;
	this->isLocalStart = False;
	PrintDataMng_DataClear(this);
	
	FATFS_CloseFile(&this->prtFile);
}

/*******************************************************************
功能：
作成者：
作成日期：2017/5/27
参数：
返回值：无
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





