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

	GPIO_InitStructure.GPIO_Pin = KEY_UP_PIN;	         //�������ø�λ����������
	GPIO_InitStructure.GPIO_Mode = KEY_SET_MODE;         //��λ����һ����ڸߵ�ƽ�ϣ�������ģʽѡ���������� 
	
	GPIO_InitStructure.GPIO_Pin=KEY_PORT_PIN;	         //ѡ����Ҫ���õİ������ڵ�IO��
	GPIO_InitStructure.GPIO_Mode=KEY_MODE;               //���ð�������ģʽ������ģʽ��

	GPIO_Init(KEY_PORT,&GPIO_InitStructure);		     //��ʼ��GPIO
	
}

u8 KEY_Scan(u8 mode)                                     //����ɨ�躯��
{
	static u8 key = 1;
	if (key == 1 && (K_UP == 1 || K_DOWN == 0 || K_LEFT == 0 || K_RIGHT == 0)) 
	{
		delay_ms(10);  
		key = 0;
		if (K_UP == 1)
		{
			return KEY_UP;
		}
		else if (K_DOWN == 0)
		{
			return KEY_DOWN;
		}
		else if (K_LEFT == 0)
		{
			return KEY_LEFT;
		}
		else
		{
			return KEY_RIGHT;
		}
	}
	else if (K_UP == 0 && K_DOWN == 1 && K_LEFT == 1 && K_RIGHT == 1) 
	{
		key = 1;
	}
	if (mode == 1) 
	{
		key = 1;
	}
	return 0;
}







