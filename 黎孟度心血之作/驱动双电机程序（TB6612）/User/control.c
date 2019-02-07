/* Includes ------------------------------------------------------------------*/
#include "control.h"
#include "motor.h"

/*******************************************************************************
* 函 数 名         : MOTOR_CONTROL
* 函数功能		   : 电机驱动tb6612逻辑配置
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void MOTOR_CONTROL(int Voltage)
{
	if(Voltage>0)
	{
	    GPIO_SetBits(GPIOB, GPIO_Pin_14 );		   //电机控制模块AIN1端 PB14		    
        GPIO_ResetBits(GPIOB, GPIO_Pin_15 );       //电机控制模块AIN2端 PB15	

		GPIO_SetBits(GPIOB, GPIO_Pin_13 );		   //电机控制模块BIN1端 PB13		    
        GPIO_ResetBits(GPIOB, GPIO_Pin_12 );       //电机控制模块BIN2端 PB12	
	}
	else
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_15 );		   //电机控制模块AIN1端 PB14			    
        GPIO_ResetBits(GPIOB, GPIO_Pin_14 );       //电机控制模块AIN2端 PB15	
  
		GPIO_SetBits(GPIOB, GPIO_Pin_12 );		   //电机控制模块BIN1端 PB12		    
        GPIO_ResetBits(GPIOB, GPIO_Pin_13 );       //电机控制模块BIN2端 PB13	
			
		Voltage=-Voltage;		
	}
	TIM_SetCompare3(TIM2,Voltage);
	//TIM2与Voltage对比，不相同则翻转波形，调节PWM占空比
	TIM_SetCompare4(TIM2,Voltage);
	//TIM3与Voltage对比，不相同则翻转波形，调节PWM占空比
}

/***************************TB6612电机驱动控制逻辑表****************************
                   AIN1  AIN2  BIN1  BIN2  PWMA  PWMB  A01/A02
                    1     0     1     0      1     1    正转
                    0     1     0     1      1     1    反转
                    1     1     1     1      1     1    刹车
                    0     0     0     0      1     1    自由停车
                    X     X     X     X      0     0    刹车
*******************************************************************************/

