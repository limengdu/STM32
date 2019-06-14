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
void Ultcontrol(void)
{
		if(Distance_Average<15.0)
		{
			Set_Joint_Angle(0);
			MotorSpeedSetOne(-1500);
			Delay_ms(900);
		}
		
	  if(Distance_Average>15.0 && Distance_Average<25.0)
		{
			MotorSpeedSetOne(-1300);
			Delay_ms(900);
			Set_Joint_Angle(30);
			MotorSpeedSetOne(1700);
			Delay_ms(900);
//			Set_Joint_Angle(-5);
		}
		
		if(Distance_Average>25.0 && Distance_Average<50.0)
		{
//			MotorSpeedSetOne(1500);
//			Delay_ms(900);
			Set_Joint_Angle(25);
			MotorSpeedSetOne(1700);
			Delay_ms(900);
//			Set_Joint_Angle(-5);
		}
		
		else
		{
			Set_Joint_Angle(0);
			MotorSpeedSetOne(1200);
		}
}







