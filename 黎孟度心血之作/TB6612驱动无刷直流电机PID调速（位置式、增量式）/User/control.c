/* Includes ------------------------------------------------------------------*/
#include "control.h"

extern int Moto1;
extern int b;

/*******************************************************************************
* �� �� ��         : MOTOR_CONTROL
* ��������		   : �������tb6612�����߼��趨
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void MOTOR_CONTROL(int moto1)
{
	//���1
	if(moto1>0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_11);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
	else
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	}
	PWMA=myabs(moto1);
//	TIM_SetCompare1(TIM1,PWMA);
	
//	//���2
//	if(moto1>0)
//	{
//		GPIO_SetBits(GPIOB,GPIO_Pin_14);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
//	}
//	else
//	{
//		GPIO_SetBits(GPIOB,GPIO_Pin_15);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
//	}
//  PWMB=myabs(moto2);
}


int myabs(int a)
{ 		   
	int temp;
	if(a<0)  temp=-a;  
	else     temp=a;
	return temp;
}

void Xianfu_Pwm(int *moto_value,int compare_value)
{
    if(*moto_value < -compare_value) 
		{
			*moto_value = -compare_value;
		}			
		if(*moto_value > compare_value)  
		{
			*moto_value = compare_value;
		}
}

/***************************TB6612������������߼���****************************
                   AIN1  AIN2  BIN1  BIN2  PWMA  PWMB  A01/A02
                    1     0     1     0      1     1    ��ת
                    0     1     0     1      1     1    ��ת
                    1     1     1     1      1     1    ɲ��
                    0     0     0     0      1     1    ����ͣ��
                    X     X     X     X      0     0    ɲ��
*******************************************************************************/
