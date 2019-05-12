/*-------------------------------------------------------------------------------
文件名称：tracking.c
文件描述：飞思卡尔智能车巡线相关功能函数   
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#include "tracking.h"
#include "delay.h"
#include "steering_engine.h"
#include "motor.h"

/*-------------------------------------------------------------------------------
函数名称：Tracking_Control
程序描述：巡线外设初始化函数
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void Tracking_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);													// 打开PE口时钟
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3  |GPIO_Pin_4 | GPIO_Pin_5;		// PE1到PE5引脚设置	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;															// 端口速度
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;												// 端口模式，此为浮空输入模式
	GPIO_Init(GPIOE, &GPIO_InitStructure);																				// 初始化对应的端口
}

/*-------------------------------------------------------------------------------
函数名称：Tracking_Control
程序描述：巡线控制函数
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void Tracking_Control(void)																											// 对5路传感器的状态经行判断
{ 
	if((S1_Tracking == 1) && (S2_Tracking == 1) && (S3_Tracking == 1) && (S4_Tracking == 0) && (S5_Tracking == 1))                    
	{
		Set_Joint_Angle(15);	
    Delay_ms(50);
	}
	else if((S1_Tracking == 1) && (S2_Tracking == 1) && (S3_Tracking == 1) && (S4_Tracking == 0) && (S5_Tracking == 0))
	{
		Set_Joint_Angle(20);
	}
	
	else if((S1_Tracking == 1) && (S2_Tracking == 1) && (S3_Tracking == 1) && (S4_Tracking == 1) && (S5_Tracking == 0))
	{   
		Set_Joint_Angle(35);
		Delay_ms(450);
	}
	
	else if((S1_Tracking == 1) && (S2_Tracking == 0) && (S3_Tracking == 1) && (S4_Tracking == 1) && (S5_Tracking == 1))
	{
		Set_Joint_Angle(-15);
		Delay_ms(50);
	}
	
	else if((S1_Tracking == 0) && (S2_Tracking == 0) && (S3_Tracking == 1) && (S4_Tracking == 1) && (S5_Tracking == 1))
	{
		Set_Joint_Angle(-20);
	}
	
  else if((S1_Tracking == 0) && (S2_Tracking == 1) && (S3_Tracking == 1) && (S4_Tracking == 1) && (S5_Tracking == 1))
	{   
		Set_Joint_Angle(-35);	
		Delay_ms(450);
	}

	else 
	{
		Set_Joint_Angle(0);
	}
}



