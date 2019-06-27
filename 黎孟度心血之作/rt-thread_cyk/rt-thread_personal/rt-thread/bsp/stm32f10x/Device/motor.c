#include "motor.h"

/*-------------------------------------------------------------------------------
函数名称：MotorSpeedSetOne
函数描述：电机1转速/转向设置
输入参数：电机速度
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void MotorSpeedSetOne(s32 MotorSpeed)
{	
#ifdef MOTOR_CONTROLL_WAY
	s32 PwmOne_Set,PwmOne_Mode;

	if (MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;		// 上限 CCR的值必须小于或等于ARR的值
	if (MotorSpeed < -(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);	// 下限 

	if (MotorSpeed < 0 ) 
	{ 
		PwmOne_Set = -MotorSpeed; 
		PwmOne_Mode = MotorOneBack;
	}
	
	else 
	{ 
		PwmOne_Set = MotorSpeed; 
		PwmOne_Mode = MotorOneForward;
	}
	
//	if (PwmOne_Mode) {TIM8->CCR1 = MotorSpdZero; TIM8->CCR2 = PwmOne_Set;} 			// MotorOneForward
//	else { TIM8->CCR1 = PwmOne_Set; TIM8->CCR2 = MotorSpdZero;} 								// MotorOneBack	
		
	if (PwmOne_Mode) 																														//MotorOneForward
	{
		TIM_SetCompare1(TIM8, MotorSpdZero);
		TIM_SetCompare2(TIM8, PwmOne_Set);
	} 			
	else 																																				//MotorOneBack	
	{ 
		TIM_SetCompare1(TIM8, PwmOne_Set);
		TIM_SetCompare2(TIM8, MotorSpdZero);
	} 								

#else
  s32 PwmOne_Mode;
	
	(MotorSpeed >= 0) ? (PwmOne_Mode = MotorOneForward) : (PwmOne_Mode = MotorOneBack);						//判断速度是否大于0，PwmOne作为电机旋转方向标记
	
	MotorSpeed = abs(MotorSpeed);                                          		//获取MotorSpeed的绝对值
	if (MotorSpeed > PWMPeriod-PWMLOSS)
	{
		MotorSpeed = PWMPeriod-PWMLOSS;																					//如果速度超过PWMPeriod-PWMLOSS的速度值，就等于其最大值
	}        
	if (PwmOne_Mode)                                                          //控制电机正反转
	{																																								
		TIM_SetCompare1(TIM8, MotorSpdZero);
		TIM_SetCompare2(TIM8, MotorSpeed);
	} 			
	else 
	{ 
		TIM_SetCompare1(TIM8, MotorSpeed);
		TIM_SetCompare2(TIM8, MotorSpdZero);
	} 									
#endif	
}
