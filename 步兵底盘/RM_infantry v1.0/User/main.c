#include "user_code.h"

/*RM STM32F427||Hx模板 */

//RCC_ClocksTypeDef RCC_Clocks;
int main(void)
{
//	RCC_GetClocksFreq(&RCC_Clocks);
     Init();
	
	/* 在这里添加你自己的程序 */
	while(1)
	{
//	LED1_TOGGLE;
//  delay_ms(500)
    Test();

	}
}

