/* Includes ------------------------------------------------------------------*/
#include "barrier.h"
#include "ultrasonic.h"
#include "control.h"
#include "motor.h"
#include "delay.h"
#include "steering_engine.h"

/*******************************************************************************
* �� �� ��         : DelayCheck
* ��������		     : ��ʱ��ͬʱ��ⳬ������һ�������ϰ����ֹͣ��������ʱ
* ��    ��         : ʱ�䡪������
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void Ultcontrol(int ms)
{
	while(ms--)
	{
		if(distance_cm<60.0)
		{
			Set_Joint_Angle(30);
			MotorSpeedSetOne(600);
			Delay_ms(500);
			Set_Joint_Angle(-5);
			MotorSpeedSetOne(700);
			return;
		}
	}
}







