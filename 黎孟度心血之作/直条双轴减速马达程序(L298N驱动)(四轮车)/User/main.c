/*******************************************************************************
模板制作：  华南理工大学广州学院野狼队
程序名：	四个直条双轴减速马达小车行驶
编写人：	黎孟度
编写时间：	2019年1月16日
硬件支持：	STM32F103ZET6及其驱动板　  

修改日志：　　
1-	

说明：
 # 本程序是在芯片为STM32F103ZET6的硬件基础上编写的，移植需了解硬件接口差异。
 # 本模板加载了光电编码器的测速模块，可实现电机测速。
 # 可根据自己的需要增加或删减。
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "motor.h"
#include "SpeedCtrol.h"
#include "tim.h"

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
unsigned char continue_time=0;

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 初始化配置
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
int main(void)
{
	GPIOCLK_Init();  //时钟初始化配置
	TIM2_Init();     //定时器TIM2初始化
	MotorInit();     //电机IO初始化
	MeasureInit();   //测速模块IO初始化
	ClearMeasure();  //清除测速测量值

	while(1)
	{	 
		
	}
}
/****************** (C) COPYRIGHT 2019 黎孟度心血之作 **************************
******************************END OF FILE**************************************/
