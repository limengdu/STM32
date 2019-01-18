#include "beep.h"
#include "SysTick.h"

void BEEP_Init(void)                                     //�������Ľӿڳ�ʼ��
{ 
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    GPIO_InitStructure.GPIO_Pin = BEEP_PIN;              //ѡ��˿ں�                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //ѡ��IO�ӿڹ�����ʽ       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //����IO�ӿ��ٶȣ�2/10/50MHz��    
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);	
	
	GPIO_SetBits(BEEP_PORT,BEEP_PIN);                    //�������ӿ�����ߵ�ƽ1		
}

void BEEP_1(void)                                        //��������һ��
{ 
	u16 i;
	for(i=0;i<200;i++)
	{
		GPIO_ResetBits(BEEP_PORT, BEEP_PIN);             //�������ӿ����0
		delay_us(500);                                   //��ʱ		
		GPIO_SetBits(BEEP_PORT, BEEP_PIN);               //�������ӿ�����ߵ�ƽ1
		delay_us(500);                                   //��ʱ		
	}
}

 
/*
ѡ��IO�ӿڹ�����ʽ��
GPIO_Mode_AIN ģ������
GPIO_Mode_IN_FLOATING ��������
GPIO_Mode_IPD ��������
GPIO_Mode_IPU ��������
GPIO_Mode_Out_PP �������
GPIO_Mode_Out_OD ��©���
GPIO_Mode_AF_PP �����������
GPIO_Mode_AF_OD ���ÿ�©���
*/
