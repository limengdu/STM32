/*******************************************************************************
模板制作：华南理工大学广州学院野狼队
程序名：	小车游华广程序
编写人：	黎孟度
编写时间：2019年5月24日
硬件支持：STM32F103ZET6
修改日志：　　
1-	
	
说明：
 # 本程序是基于STM32F103ZET6开发板的硬件基础上编写的，移植需了解硬件接口差异。
 # 本模板是在电机驱动板下实现的
 # 可根据自己的需要增加或删减。
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "interface.h"
#include "IRCtrol.h"
#include "motor.h"
#include "uart.h"

//全局变量定义
unsigned int speed_count=0;//占空比计数器 50次一周期
int front_left_speed_duty=SPEED_DUTY;
int front_right_speed_duty=SPEED_DUTY;
int behind_left_speed_duty=SPEED_DUTY;
int behind_right_speed_duty=SPEED_DUTY;

unsigned char tick_5ms = 0;//5ms计数器，作为主函数的基本周期
unsigned char tick_1ms = 0;//1ms计数器，作为电机的基本计数器
unsigned char tick_200ms = 0;//刷新显示

char ctrl_comm = COMM_STOP;//控制指令
char ctrl_comm_last = COMM_STOP;//上一次的指令
unsigned char continue_time=0;
unsigned char bt_rec_flag=0;//蓝牙控制标志位

/*******************************************************************************
* 函 数 名         : SearchRun
* 函数功能		     : 循迹，通过判断三个光电对管的状态来控制小车运动
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void SearchRun(void)
{
	//三路都检测到
	if(SEARCH_M_IO == BLACK_AREA && SEARCH_L_IO == BLACK_AREA && SEARCH_R_IO == BLACK_AREA)
	{
		ctrl_comm = COMM_UP;
		return;
	}
	
	if(SEARCH_R_IO == BLACK_AREA)//右
	{
		ctrl_comm = COMM_RIGHT;
	}
	else if(SEARCH_L_IO == BLACK_AREA)//左
	{
		ctrl_comm = COMM_LEFT;
	}
	else if(SEARCH_M_IO == BLACK_AREA)//中
	{
		ctrl_comm = COMM_UP;
	}
}


/*******************************************************************************
* 函 数 名         : main
* 函数功能		     : 循迹，通过判断三个光电对管的状态来控制小车运动
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
int main(void)
{
	delay_init();
	GPIOCLKInit();
	UserLEDInit();
	IRCtrolInit();
	TIM2_Init();
	MotorInit();
	ServoInit();
	RedRayInit();
	USART3Conf(9600);
	CarStop();

 while(1)
 {	 
	 		if(tick_5ms >= 5)
		{
			tick_5ms = 0;
			tick_200ms++;
			if(tick_200ms >= 40)
			{
				tick_200ms = 0;
				LEDToggle(LED_PIN);
			}
			
			if(a==2)SearchRun();
			
			if(ctrl_comm_last != ctrl_comm)//指令发生变化
			{
				ctrl_comm_last = ctrl_comm;
				switch(ctrl_comm)
				{
					case COMM_UP:    CarGo();break;
					case COMM_DOWN:  CarBack();break;
					case COMM_LEFT:  CarLeft();break;
					case COMM_RIGHT: CarRight();break;
					case COMM_STOP:  CarStop();break;
					default : break;
				}
				Delayms(10);//防抖
			}
		}
 }
}

