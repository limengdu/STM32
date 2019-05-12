/*-------------------------------------------------------------------------------
�ļ����ƣ�control.c
�ļ���������˼�������ܳ����ƺ���.c�ļ�    
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
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

extern bool __Init_flag;
extern KEY_RELEASE_Status __Key_release_flag;
extern u8 USARTx_RX_BUF[USART_REC_LEN];
u8 key;
s16 key_counter;
s32 key_counter_value;
extern __IO uint8_t  __PID_Start_flag;
extern PID_TypeDef  sPID;

/*-------------------------------------------------------------------------------
�������ƣ�Freescale_Device_Init
������������˼�������ܳ������豸��ʼ����
�����������
���ز�������
��    ע�����������ϵ��ʼ�������ϵ�ִ��һ�Σ���
---------------------------------------------------------------------------------*/
void Freescale_Device_Init()
{
	Set_Joint_Angle(0);
	__Init_flag = SUCCESS;
}

/*-------------------------------------------------------------------------------
�������ƣ�Freescale_Control_Kernel
������������˼�������ܳ����ƺ��ġ�
�����������
���ز�������
��    ע�������������ƣ���ϵͳ��������ȡ����TIM7��ʱ�����ڡ�
---------------------------------------------------------------------------------*/
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
	if(key == __key_1)																													// KEY1�����٣�
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
		 __PID_Start_flag = 1;
	}
	else if(key == __key_2)																											// KEY2�����٣�
	{	 
//			if(__Key_release_flag == REL_SET)
//			{
//				sPID.SetPoint += 2;
//				if(sPID.SetPoint >= 12)
//				{
//					sPID.SetPoint = 12;
//				}
			__Key_release_flag = UN_REL_SET;
		}
		__PID_Start_flag = 1;
	}
	else if(key == __key_3)																											// KEY3��ֹͣ��
	{	 
		if(__Key_release_flag == REL_SET)
		{
			sPID.SetPoint = 0;
			__Key_release_flag = UN_REL_SET;
		}
	}
#endif

#ifdef USE_AUTO
		Tracking_Control();
#endif
}
