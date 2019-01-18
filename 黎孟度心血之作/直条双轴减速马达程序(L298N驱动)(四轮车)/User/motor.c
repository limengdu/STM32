/* Includes ------------------------------------------------------------------*/
#include "motor.h"
#include "tim.h"
#include "stm32f10x.h"

/*******************************************************************************
* 函 数 名         : MotorGPIO_Configuration
* 函数功能		   : 配置电机GPIO
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
* 函数功能		   : 根据占空比驱动电机转动
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void CarMove(void)
{   
	
	 BEHIND_RIGHT_EN;    //使能左右电机
	
 //左前轮（由于左右两边电机分别用一个驱动，左边用左后轮操作即可）
//	if(front_left_speed_duty > 0)//向前
//	{
//		if(speed_count < front_left_speed_duty)
//		{
//			FRONT_LEFT_GO;
//		}
//	    else
//		{
//			FRONT_LEFT_STOP;
//		}
//	}
//	else if(front_left_speed_duty < 0)//向后
//	{
//		if(speed_count < (-1)*front_left_speed_duty)
//		{
//			FRONT_LEFT_BACK;
//		}
//		else
//		{
//			FRONT_LEFT_STOP;
//		}
//	}
//	else                //停止
//	{
//		FRONT_LEFT_STOP;
//	}
	
	//右前轮（由于左右两边电机分别用一个驱动，右边用右前轮操作即可）
	if(front_right_speed_duty > 0)//向前
	{
		if(speed_count < front_right_speed_duty) 
		{                      //speed_count最大为50，front_right_speed_duty为40
			FRONT_RIGHT_GO;    
		}
		else                   //有10ms的停止时间,即为“空”的时间
		{
			FRONT_RIGHT_STOP;  
		}
		//停止的作用是产生平均速度
		//基本思路是通过定时器产生中断，通过时间调节电机占空比实现调速
	}
	else if(front_right_speed_duty < 0)//向后
	{
		if(speed_count < (-1)*front_right_speed_duty)
		{
			FRONT_RIGHT_BACK;
		}
		else                //停止
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
		}	
		else                //停止
		{
			BEHIND_LEFT_STOP;
		}
	}
	else if(behind_left_speed_duty < 0)//向后
	{
		if(speed_count < (-1)*behind_left_speed_duty)
		{
			BEHIND_LEFT_BACK;
		}	
		else                //停止
		{
			BEHIND_LEFT_STOP;
		}
	}
	else                //停止
	{
		BEHIND_LEFT_STOP;
	}
	
//	//右后轮
//	if(behind_right_speed_duty > 0)//向前
//	{
//		if(speed_count < behind_right_speed_duty)
//		{
//			BEHIND_RIGHT_GO;
//		}	
//	    else                //停止
//		{
//			BEHIND_RIGHT_STOP;
//		}
//	}
//	else if(behind_right_speed_duty < 0)//向后
//	{
//		if(speed_count < (-1)*behind_right_speed_duty)
//		{
//			BEHIND_RIGHT_BACK;
//		}	
//	    else                //停止
//		{
//			BEHIND_RIGHT_STOP;
//		}
//	}
//	else                //停止
//	{
//		BEHIND_RIGHT_STOP;
//	}
}

/*******************************************************************************
* 函 数 名         : CarGo
* 函数功能		   : 小车前进
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void CarGo(void)
{
	//front_left_speed_duty=SPEED_DUTY;
	front_right_speed_duty=SPEED_DUTY; // 左电机
	behind_left_speed_duty=SPEED_DUTY; //右电机
	//behind_right_speed_duty=SPEED_DUTY;
}

/*******************************************************************************
* 函 数 名         : CarBack
* 函数功能		   : 小车后退
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void CarBack(void)
{
	front_left_speed_duty=-SPEED_DUTY;
	front_right_speed_duty=-SPEED_DUTY;
	behind_left_speed_duty=-SPEED_DUTY;
	behind_right_speed_duty=-SPEED_DUTY;
}

/*******************************************************************************
* 函 数 名         : CarRight
* 函数功能		   : 小车右转
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void CarRight(void)
{
	front_left_speed_duty=-SPEED_DUTY/2;
	front_right_speed_duty=SPEED_DUTY;
	behind_left_speed_duty=-SPEED_DUTY/2;
	behind_right_speed_duty=SPEED_DUTY+10;//增加后轮驱动力
}

/*******************************************************************************
* 函 数 名         : CarLeft
* 函数功能		   : 小车左转
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void CarLeft(void)
{
	front_left_speed_duty=SPEED_DUTY;
	front_right_speed_duty=-SPEED_DUTY/2;
	behind_left_speed_duty=SPEED_DUTY+10;//增加后轮驱动力
	behind_right_speed_duty=-SPEED_DUTY/2;
}
/*若要实现小车左转、右转或者后退，则需要将对应函数放到定时器TIM2中断服务函数当
中，且需在CarMove();之后。还需要注意的是要把原来CarGo();注释掉*/

/*******************************************************************************
* 函 数 名         : CarStop
* 函数功能		   : 小车停止
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void CarStop(void)
{
	front_left_speed_duty=0;
	front_right_speed_duty=0;
	behind_left_speed_duty=0;
	behind_right_speed_duty=0;
}

/*******************************************************************************
* 函 数 名         : MotorInit
* 函数功能		   : 电机初始化
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void MotorInit(void)
{
	MotorGPIO_Configuration();
	CarStop();
}


