#include "control.h"

void MOTOR_CONTROL1(int moto1)
{
	//电机1
	if(moto1>0)  //如果计算的PWM为正值则电机正转
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_11);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
	else         //如果计算的PWM为负值则电机反转
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	}
	PWMA=myabs(moto1);
}

void MOTOR_CONTROL2(int moto2)
{
	//电机2
	if(moto2>0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	}
	else
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	}
    PWMB=myabs(moto2);
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
