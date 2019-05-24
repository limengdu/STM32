#include "motor.h"
#include "interface.h"
#include "stm32f10x.h"


/*******************************************************************************
* 函 数 名         : MotorGPIO_Configuration
* 函数功能		     : 电机引脚配置
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void MotorGPIO_Configuration(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_F_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_Init(FRONT_LEFT_F_GPIO, &GPIO_InitStructure);    
	
	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_B_PIN;	
	GPIO_Init(FRONT_LEFT_B_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_F_PIN;	
	GPIO_Init(FRONT_RIGHT_F_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_B_PIN;	
	GPIO_Init(FRONT_RIGHT_B_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_LEFT_F_PIN;	
	GPIO_Init(BEHIND_LEFT_F_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_LEFT_B_PIN;	
	GPIO_Init(BEHIND_LEFT_B_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_RIGHT_F_PIN;	
	GPIO_Init(BEHIND_RIGHT_F_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_RIGHT_B_PIN;	
	GPIO_Init(BEHIND_RIGHT_B_GPIO, &GPIO_InitStructure);  
	
}


/*******************************************************************************
* 函 数 名         : CarMove
* 函数功能		     : 根据占空比驱动电机转动
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void CarMove(void)
{   
	
	 BEHIND_RIGHT_EN;
	
		//右前轮
	if(front_right_speed_duty > 0)//向前
	{
		if(speed_count < front_right_speed_duty)
		{
			FRONT_RIGHT_GO;
		}else                //停止
		{
			FRONT_RIGHT_STOP;
		}
	}
	else if(front_right_speed_duty < 0)//向后
	{
		if(speed_count < (-1)*front_right_speed_duty)
		{
			FRONT_RIGHT_BACK;
		}else                //停止
		{
			FRONT_RIGHT_STOP;
		}
	}
	else                //停止
	{
		FRONT_RIGHT_STOP;
	}
	
	//左后轮
	if(behind_left_speed_duty > 0)//向前
	{
		if(speed_count < behind_left_speed_duty)
		{
			BEHIND_LEFT_GO;
		}	else                //停止
		{
			BEHIND_LEFT_STOP;
		}
	}
	else if(behind_left_speed_duty < 0)//向后
	{
		if(speed_count < (-1)*behind_left_speed_duty)
		{
			BEHIND_LEFT_BACK;
		}	else                //停止
		{
			BEHIND_LEFT_STOP;
		}
	}
	else                //停止
	{
		BEHIND_LEFT_STOP;
	}
}

//向前
void CarGo(void)
{
	//front_left_speed_duty=SPEED_DUTY;
	front_right_speed_duty=SPEED_DUTY;
	behind_left_speed_duty=SPEED_DUTY;
	//behind_right_speed_duty=SPEED_DUTY;
}

//后退
void CarBack(void)
{
	front_left_speed_duty=-SPEED_DUTY;
	front_right_speed_duty=-SPEED_DUTY;
	behind_left_speed_duty=-SPEED_DUTY;
	behind_right_speed_duty=-SPEED_DUTY;
}

//向左
void CarLeft(void)
{
	front_left_speed_duty=-20;
	front_right_speed_duty=SPEED_DUTY;
	behind_left_speed_duty=-20;
	behind_right_speed_duty=SPEED_DUTY+10;//增加后轮驱动力
}

//向右
void CarRight(void)
{
	front_left_speed_duty=SPEED_DUTY;
	front_right_speed_duty=-20;
	behind_left_speed_duty=SPEED_DUTY+10;//增加后轮驱动力
	behind_right_speed_duty=-20;
}

//停止
void CarStop(void)
{
	front_left_speed_duty=0;
	front_right_speed_duty=0;
	behind_left_speed_duty=0;
	behind_right_speed_duty=0;
}

void MotorInit(void)
{
	MotorGPIO_Configuration();
	CarStop();
}

