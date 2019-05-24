/* Includes ------------------------------------------------------------------*/
#include "barrier.h"
#include "ultrasonic.h"
#include "control.h"
#include "motor.h"
#include "delay.h"
#include "steering_engine.h"

/*******************************************************************************
* 函 数 名         : DelayCheck
* 函数功能		     : 延时的同时检测超声波，一旦发生障碍物，就停止并跳出延时
* 输    入         : 时间——毫秒
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void Ultcontrol(int ms)
{
	while(ms--)
	{
		if(distance_cm<60.0)
		{
			Set_Joint_Angle(30);
			MotorSpeedSetOne(-2500);
			Delay_ms(1800);
			Set_Joint_Angle(-5);
			MotorSpeedSetOne(1500);
			return;
		}
	}
}







