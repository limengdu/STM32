/* Includes ------------------------------------------------------------------*/
#include "control.h"


/*******************************************************************************
* �� �� ��         : MOTOR_CONTROL1
* ��������		   : �������tb6612�����߼��趨�Լ�PWMA�趨
* ��    ��         : ���1��PWMAֵ������PID���㣩
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void MOTOR_CONTROL1(int moto1)
{
	if(moto1>0)         //��������PWMΪ��ֵ������ת
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_11);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
	else                //��������PWMΪ��ֵ������ת
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	}
	PWMA=myabs(moto1);  //PWMA���ݸ�CCR1
}


/*******************************************************************************
* �� �� ��         : MOTOR_CONTROL2
* ��������		   : �������tb6612�����߼��趨�Լ�PWMB�趨
* ��    ��         : ���2��PWMBֵ������PID���㣩
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void MOTOR_CONTROL2(int moto2)
{
	if(moto2>0)         //��������PWMΪ��ֵ������ת
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	}
	else                //��������PWMΪ��ֵ������ת
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	}
    PWMB=myabs(moto2);  //PWMB���ݸ�CCR4
}


/*******************************************************************************
* �� �� ��         : myabs
* ��������		   : ����ֵ����
* ��    ��         : ��Ҫȡ����ֵ����ֵ
* ��    ��         : ȡ����ֵ֮�����ֵ
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
int myabs(int a)
{ 		   
	int temp;
	if(a<0)  temp=-a;  
	else     temp=a;
	return temp;
}


/*******************************************************************************
* �� �� ��         : Xianfu_Pwm
* ��������		   : ����PWM��ֵ�����ⳬ�����ֵ�����������趨һ������ʱ����7200��
                     �޷����ֵΪ7100
* ��    ��         : *moto_value������PID����֮���PWM
                     compare_value���޷�PWM���ֵ
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void Xianfu_Pwm(int *moto_value,int compare_value)
{
    if(*moto_value < -compare_value)       //�����޷�
		{
			*moto_value = -compare_value;
		}			
		if(*moto_value > compare_value)    //�����޷�
		{
			*moto_value = compare_value;
		}
}
