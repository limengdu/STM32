#include "led.h"

void LED_Init()                                         //LED��ʼ������
{
	GPIO_InitTypeDef GPIO_InitStructure;                //����ṹ�����
	
	RCC_APB2PeriphClockCmd(LED_PORT_RCC,ENABLE);        //����ʱ��

    GPIO_InitStructure.GPIO_Pin   = LED_PIN;            //�������ź�
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;   //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //�������Ƶ��Ϊ50MHz
	GPIO_Init(LED_PORT,&GPIO_InitStructure);            //��ʼ������
	
	GPIO_SetBits(LED_PORT,LED_PIN);                     //��LED��������ߵ�ƽ��ȷ����ʼ״̬Ϩ�����е�
}







