/* Includes ------------------------------------------------------------------*/
#include "ccdcontrol.h"
#include "ccd.h"
#include "motor.h"
#include "steering_engine.h"

extern u8 CCD_Middle;

/*******************************************************************************
* �� �� ��         : ccdcon
* ��������		     : ����ccdʶ�����Ѱ������
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
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

