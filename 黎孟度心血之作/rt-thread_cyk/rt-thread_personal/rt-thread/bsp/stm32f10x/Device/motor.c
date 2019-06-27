#include "motor.h"

/*-------------------------------------------------------------------------------
�������ƣ�MotorSpeedSetOne
�������������1ת��/ת������
�������������ٶ�
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void MotorSpeedSetOne(s32 MotorSpeed)
{	
#ifdef MOTOR_CONTROLL_WAY
	s32 PwmOne_Set,PwmOne_Mode;

	if (MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;		// ���� CCR��ֵ����С�ڻ����ARR��ֵ
	if (MotorSpeed < -(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);	// ���� 

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
	
	(MotorSpeed >= 0) ? (PwmOne_Mode = MotorOneForward) : (PwmOne_Mode = MotorOneBack);						//�ж��ٶ��Ƿ����0��PwmOne��Ϊ�����ת������
	
	MotorSpeed = abs(MotorSpeed);                                          		//��ȡMotorSpeed�ľ���ֵ
	if (MotorSpeed > PWMPeriod-PWMLOSS)
	{
		MotorSpeed = PWMPeriod-PWMLOSS;																					//����ٶȳ���PWMPeriod-PWMLOSS���ٶ�ֵ���͵��������ֵ
	}        
	if (PwmOne_Mode)                                                          //���Ƶ������ת
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
