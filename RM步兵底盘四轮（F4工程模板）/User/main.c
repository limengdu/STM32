#include "user_code.h"

/*RM STM32F427||Hxģ�� */

//RCC_ClocksTypeDef RCC_Clocks;
int main(void)
{
//	RCC_GetClocksFreq(&RCC_Clocks);
     Init();             //���ֶ����ĳ�ʼ������
	
	/* ������������Լ��ĳ��� */
	while(1)
	{
//	LED1_TOGGLE;
//  delay_ms(500)
    Test();              //���ֶ��������в���
		
		
		
		
		//��Ʋ���
		GPIO_SetBits(GPIOG,LED_Pin);   //RM������ߵ�ƽ��Ϩ��
		delay_ms(500);
		GPIO_ResetBits(GPIOG,LED_Pin);
		delay_ms(200);
		

	}
}

