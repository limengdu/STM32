/*-------------------------------------------------------------------------------
�ļ����ƣ�key.c
�ļ�������������ع��ܺ�����    
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "key.h"
#include "delay.h"

KEY_RELEASE_Status __Key_release_flag;

/*-------------------------------------------------------------------------------
�������ƣ�KEY_Init
�����������������ų�ʼ�����򿪶˿�ʱ�ӣ����ö˿����ţ��˿ڹ���Ƶ�ʣ��˿�����ģʽ 
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);													// ��PA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);													// ��PE��ʱ��
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_4 | GPIO_Pin_5;											// PA4��PA5��������	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;															// �˿��ٶ�
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;																// �˿�ģʽ����Ϊ��������ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);																				// ��ʼ����Ӧ�Ķ˿�
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_15;																	// PE15��������	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;															// �˿��ٶ�
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;																// �˿�ģʽ����Ϊ��������ģʽ
	//GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;															 // �˿�ģʽ����Ϊ��������ģʽ
	GPIO_Init(GPIOE, &GPIO_InitStructure);																				// ��ʼ����Ӧ�Ķ˿�
}

/*-------------------------------------------------------------------------------
�������ƣ�KEY_Scan
������������Ҫ�����жϰ���״̬
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
u8 KEY_Scan(void)
{	 
	if((KEY1  == 1) || (KEY2 == 1) || (KEY3 == 1))
	{
		Delay_ms(10);																																// ȥ���� 
		
		if(KEY1 == 1) return 1;
		else if(KEY2 == 1) return 2;
		else if(KEY3 == 1) return 3;
	}
	else
	{
		__Key_release_flag = REL_SET;																								// �����ͷű��
	}
	
	return 0;																																		  // �ް�������
}
