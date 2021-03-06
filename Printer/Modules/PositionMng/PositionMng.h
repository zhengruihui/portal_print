/********************** (C) COPYRIGHT 2017 DediBot ******************************
  * @file    PositionMng.h
  * @author  Dedibot
  * @version V
  * @date    2017-05-24
  * @brief   位置控制
*********************************************************************************/
#ifndef POSITIONMNG_H
#define POSITIONMNG_H
#include "de_type.h"
#include "AxisCtrl.h"
#include "stepper.h"
#include "planner.h"
#include "Homing.h"
#include "Globals.h"


typedef struct
{	
	u8 stage;
	
	float feedRate;

	u8 totalAxesCount;
	char *stringsForParse_Origin;
	char *stringsForParse;
	
	enum _AXIS *axes;
	u8 newPosFlag[AXIS_MAX];
	long *axesOffset;
	float localScalePos[AXIS_MAX];
	
	// float globalScalePos[AXIS_MAX];
	
	/* 移动轴 */
	u8 mainAxesCount;
	u8 *mainAxesIndex;
	enum _AXIS *mainAxes;
	float mainAxesPos[AXIS_MAX];
	
	POSPARAM mainPosParam;
	
	/* 挤料轴 */
	u8 extruderAxesCount;
	u8 *extruderAxesIndex;
	enum _AXIS *extruderAxes;
	float extruderAxesPos[AXIS_MAX];
	
	POSPARAM extruderPosParam;
	
	/* 自由轴 */
	u8 freeAxesCount;
	u8 *freeAxesIndex;
	enum _AXIS *freeAxes;
	float freeAxesPos[AXIS_MAX];
	
	POSPARAM freePosParam;
	
	/* 线性插补运动模块 */
	PLANNER *mainPlanner;
	MOVE_MODULE *mainMoveModule;
	
	/* 自由轴运动模块 */
	PLANNER *freePlanner;
	MOVE_MODULE *freeMoveModule;

	/* 回原点模块 */
	HOMING_MODULE homingModule;
	
	u8 homingAxesCount;
	u8 subhomingAxesCount;
	enum _AXIS *homingAxes;
	enum _AXIS *subhomingAxes;
	char **setHomeGcode;
}POSITIONMNG;

typedef enum 
{
	STAGE_STANDARD,
	STAGE_HOMING,
	STAGE_SUBHOMING,
	
	STAGE_MAX
}STAGE;

extern void PositionMng_Clear(POSITIONMNG *this);
extern void PositionMng_MoveHome(POSITIONMNG *this);
extern bool PositionMng_IsMoveHomeFinished( POSITIONMNG *this );
extern void PositionMng_PrepareMove_Gcode( POSITIONMNG *this, char *gcode ) ;
extern void PositionMng_PrepareMove_Position(POSITIONMNG *this, float *dest, float feedrate) ;
extern void PositionMng_Set_Position(POSITIONMNG *this, float *pos, bool isAllSet) ;
extern void PositionMng_Pro( POSITIONMNG *this );
extern bool PositionMng_CanMove( POSITIONMNG *this );
extern bool PositionMng_IsMoveFinished( POSITIONMNG *this );
extern bool PositionMng_IsHomingFinished( POSITIONMNG *this ) ;
extern void PositionMng_Set_Position_Gcode( POSITIONMNG *this, char *gcode, bool isAllSet); 

extern void PositionMng_Stop_Y(POSITIONMNG *this, u8 select);
extern void PositionMng_MoveHome_Y(POSITIONMNG *this, u8 select);
extern void PositionMng_MoveHome_XY(POSITIONMNG *this);

extern void PositionMng_Init_1(POSITIONMNG *this);
extern void PositionMng_Init_2(POSITIONMNG *this);
extern void PositionMng_Init_3(POSITIONMNG *this);

extern void PositionMng_SetNormalMode(POSITIONMNG *this);
extern void PositionMng_SetInfiniteMode(POSITIONMNG *this);

#endif/* POSITIONMNG_H */

