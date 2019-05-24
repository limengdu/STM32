/*-------------------------------------------------------------------------------
�ļ����ƣ�tracking.c
�ļ���������˼�������ܳ�Ѳ����ع��ܺ���   
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "tracking.h"
#include "delay.h"
#include "steering_engine.h"
#include "motor.h"

/*-------------------------------------------------------------------------------
�������ƣ�Tracking_Control
����������Ѳ�������ʼ������
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void Tracking_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);													// ��PE��ʱ��
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3  |GPIO_Pin_4 | GPIO_Pin_5;		// PE1��PE5��������	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;															// �˿��ٶ�
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;												// �˿�ģʽ����Ϊ��������ģʽ
	GPIO_Init(GPIOE, &GPIO_InitStructure);																				// ��ʼ����Ӧ�Ķ˿�
}

/*-------------------------------------------------------------------------------
�������ƣ�Tracking_Control
����������Ѳ�߿��ƺ���
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void Tracking_Control(void)																											// ��5·��������״̬�����ж�
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



