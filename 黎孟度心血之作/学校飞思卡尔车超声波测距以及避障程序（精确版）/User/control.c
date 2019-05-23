/*-------------------------------------------------------------------------------
文件名称：control.c
文件描述：飞思卡尔智能车控制核心.c文件    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#include "control.h"
#include "steering_engine.h"
#include "string.h"
#include <stdio.h>
#include "stm32f10x_it.h"
#include "motor.h"
#include "key.h"
#include "tracking.h"
#include "pid.h"
#include "barrier.h"

extern bool __Init_flag;
extern KEY_RELEASE_Status __Key_release_flag;
extern u8 USARTx_RX_BUF[USART_REC_LEN];
u8 key;
s16 key_counter;
s32 key_counter_value;
extern __IO uint8_t  __PID_Start_flag;
extern PID_TypeDef  sPID;

/*-------------------------------------------------------------------------------
函数名称：Freescale_Device_Init
函数描述：飞思卡尔智能车控制设备初始化。
输入参数：无
返回参数：无
备    注：用于整车上电初始化（仅上电执行一次）。
---------------------------------------------------------------------------------*/
void Freescale_Device_Init()
{
	Set_Joint_Angle(-5);
	__Init_flag = SUCCESS;
}

/*******************************************************************************
* 函 数 名         : Freescale_Control_Kernel
* 函数功能		     : 飞思卡尔智能车控制核心——按键启动小车
* 输    入         : pLocalMemoryList
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void Freescale_Control_Kernel(u8* pLocalMemoryList)
{ 
#ifdef USE_KEYBOARD
	switch(USARTx_RX_BUF[0])
	{
		case 'a':	Set_Joint_Angle(-15); 
							break;
		case 'd': Set_Joint_Angle(15);	 
							break;
		case 'w': Set_Joint_Angle(0);	 
							break;
		case 's': Set_Joint_Angle(0);	 
							break;
		case 'j':	MotorSpeedSetOne(1500);	
							break;
		case 'k': MotorSpeedSetOne(-1500);	
							break;
		case ' ': MotorSpeedSetOne(0);	 
							break;
		default : break;
	}
#endif
	
#ifdef USE_KEY
	key = KEY_Scan();
	if(key == __key_1)																													// KEY1
	{
		if(__Key_release_flag == REL_SET)
		{
			key_counter_value	= -1000+key_counter*10;
			MotorSpeedSetOne(key_counter_value);
			key_counter--; 
			__Key_release_flag = UN_REL_SET;
		}
	}
	else if(key == __key_2)																											// KEY2
	{	 
		if(__Key_release_flag == REL_SET)
		{
			key_counter_value	= 1000+key_counter*10;
			MotorSpeedSetOne(key_counter_value);
			key_counter++;
			__Key_release_flag = UN_REL_SET;
		}
	}
	else if(key == __key_3)																											// KEY3
	{	 
		if(__Key_release_flag == REL_SET)
		{
			MotorSpeedSetOne(0);
			key_counter = 0;
			__Key_release_flag = UN_REL_SET;
		}
	}
#endif

#ifdef USE_KEY_PID
	key = KEY_Scan();
	if(key == __key_1)																													// KEY1（速度1500）
	{
		if(__Key_release_flag == REL_SET)
		{
//				sPID.SetPoint -= 2;
//				if(sPID.SetPoint <= -12)
//				{
//					sPID.SetPoint = -12;
//				}
//				__Key_release_flag = UN_REL_SET;
//			}
//		 __PID_Start_flag = 1;
			MotorSpeedSetOne(1000);
	}
	else if(key == __key_2)																											// KEY2（速度2000）
	{	 
//			if(__Key_release_flag == REL_SET)
//			{
//				sPID.SetPoint += 2;
//				if(sPID.SetPoint >= 12)
//				{
//					sPID.SetPoint = 12;
//				}
//			__Key_release_flag = UN_REL_SET;
//		}
//		__PID_Start_flag = 1;
		MotorSpeedSetOne(600);
	}
	else if(key == __key_3)																											// KEY3（停止）
	{	 
		if(__Key_release_flag == REL_SET)
		{
//			sPID.SetPoint = 0;
//			__Key_release_flag = UN_REL_SET;
			MotorSpeedSetOne(0);
		}
	}
#endif

#ifdef USE_AUTO
		Tracking_Control();
#endif
}
	}
