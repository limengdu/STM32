#include "key.h"
#include "stm32f10x.h"

/*******************************************************************************
* �� �� ��         : KEY_Init
* ��������		   : ������ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                 //����ṹ�����	
	RCC_APB2PeriphClockCmd(GPIO_KEY_RCC,ENABLE);         //�����������ڵ�ʱ��
	
	GPIO_InitStructure.GPIO_Pin=KEY_PORT_PIN;	         //ѡ����Ҫ���õİ������ڵ�IO��
	GPIO_InitStructure.GPIO_Mode=KEY_MODE;               //���ð�������ģʽ������ģʽ������ģʽ��

	GPIO_Init(KEY_PORT,&GPIO_InitStructure);		     //��ʼ��GPIO
	
}






