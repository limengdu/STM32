/* Includes ------------------------------------------------------------------*/
#include "ccdcontrol.h"
#include "ccd.h"
#include "motor.h"
#include "steering_engine.h"

extern u8 CCD_Middle;

/*******************************************************************************
* 函 数 名         : ccdcon
* 函数功能		     : 线性ccd识别黑线寻迹程序
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void ccdcon()
{
	if(CCD_Middle>27 && CCD_Middle<45)
	{
		Set_Joint_Angle(-5);
		MotorSpeedSetOne(1200);
	}
	
	else if(CCD_Middle<27)
	{
		Set_Joint_Angle(-15);
		MotorSpeedSetOne(1100);
	}
	
	else if(CCD_Middle>80&& CCD_Middle>45)
	{
		Set_Joint_Angle(25);
		MotorSpeedSetOne(1500);
	}
	
	else if(CCD_Middle>45)
	{
		Set_Joint_Angle(5);
		MotorSpeedSetOne(1100);
	}
}

