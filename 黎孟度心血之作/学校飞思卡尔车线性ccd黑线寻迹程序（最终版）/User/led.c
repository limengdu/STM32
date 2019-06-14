/*-------------------------------------------------------------------------------
�ļ����ƣ�led.c
�ļ���������������LED�Ĺ��ܺ�����    
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "led.h"
#include "delay.h"

/*-------------------------------------------------------------------------------
�������ƣ�LED_Init
������������ʼ��LED��ض˿ڣ��򿪶˿�ʱ�ӣ����ö˿������
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);			// ʹ��PA��PD�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;																			// PA12 ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;																	// �˿��ٶ�(MAX)			
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;																	// �˿�ģʽ����Ϊ�������ģʽ
  GPIO_Init(GPIOA, &GPIO_InitStructure);																						// ��ʼ����ӦPA�˿�
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;																				// PD3 ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;																	// �˿��ٶ�(MAX)			
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;																	// �˿�ģʽ����Ϊ�������ģʽ
  GPIO_Init(GPIOD, &GPIO_InitStructure);																						// ��ʼ����ӦPD�˿�
}

/*-------------------------------------------------------------------------------
�������ƣ�LED_State
����������LEDָʾ�ƣ�����MCU��������������ؼ�⡣
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void LED_State(void)
{
	LED1_ON;																																					// MCU���������������״ָ̬ʾ�� 1��
	LED2_OFF;
	
	Delay_ms(1000);																																		// ����LED2 ��ʱ��������
	
	LED2_ON;																																					// MCU���������������״ָ̬ʾ�� 2��
}
