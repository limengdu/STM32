/* Includes ------------------------------------------------------------------*/
#include "control.h"


/*******************************************************************************
* 函 数 名         : MOTOR_CONTROL1
* 函数功能		   : 电机驱动tb6612控制逻辑设定以及PWMA设定
* 输    入         : 电机1的PWMA值（经过PID计算）
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void MOTOR_CONTROL1(int moto1)
{
	if(moto1>0)         //如果计算的PWM为正值则电机正转
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_11);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
	else                //如果计算的PWM为负值则电机反转
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	}
	PWMA=myabs(moto1);  //PWMA传递给CCR1
}


/*******************************************************************************
* 函 数 名         : MOTOR_CONTROL2
* 函数功能		   : 电机驱动tb6612控制逻辑设定以及PWMB设定
* 输    入         : 电机2的PWMB值（经过PID计算）
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void MOTOR_CONTROL2(int moto2)
{
	if(moto2>0)         //如果计算的PWM为正值则电机正转
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	}
	else                //如果计算的PWM为负值则电机反转
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	}
    PWMB=myabs(moto2);  //PWMB传递给CCR4
}


/*******************************************************************************
* 函 数 名         : myabs
* 函数功能		   : 绝对值函数
* 输    入         : 需要取绝对值的数值
* 输    出         : 取绝对值之后的数值
*                             黎孟度心血之作                                   *
*******************************************************************************/
int myabs(int a)
{ 		   
	int temp;
	if(a<0)  temp=-a;  
	else     temp=a;
	return temp;
}


/*******************************************************************************
* 函 数 名         : Xianfu_Pwm
* 函数功能		   : 限制PWM的值，避免超过最大值，本程序中设定一个周期时间是7200，
                     限幅最大值为7100
* 输    入         : *moto_value：经过PID计算之后的PWM
                     compare_value：限幅PWM最大值
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void Xianfu_Pwm(int *moto_value,int compare_value)
{
    if(*moto_value < -compare_value)       //反向限幅
		{
			*moto_value = -compare_value;
		}			
		if(*moto_value > compare_value)    //正向限幅
		{
			*moto_value = compare_value;
		}
}
