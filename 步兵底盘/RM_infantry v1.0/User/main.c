#include "user_code.h"

/*RM STM32F427||Hxģ�� */

//RCC_ClocksTypeDef RCC_Clocks;
int main(void)
{
//	RCC_GetClocksFreq(&RCC_Clocks);
     Init();
	
	/* ������������Լ��ĳ��� */
	while(1)
	{
//	LED1_TOGGLE;
//  delay_ms(500)
    Test();

	}
}

