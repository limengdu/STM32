#include "beep.h"

void BEEP_Init()                                         //��������ʼ������
{
	GPIO_InitTypeDef GPIO_InitStructure;                 //����ṹ�����
	
	RCC_APB2PeriphClockCmd(BEEP_PORT_RCC,ENABLE);        //����ʱ��

    GPIO_InitStructure.GPIO_Pin   = BEEP_PIN;            //�������ź�
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;    //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //�������Ƶ��Ϊ50MHz
	GPIO_Init(BEEP_PORT,&GPIO_InitStructure);            //��ʼ������
	
	GPIO_SetBits(BEEP_PORT,BEEP_PIN);                    //����������������ߵ�ƽ��ȷ����ʼ״̬���������ڽ�ֹ״̬
}







