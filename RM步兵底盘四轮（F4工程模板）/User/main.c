#include "user_code.h"

/*RM STM32F427||Hx模板 */

//RCC_ClocksTypeDef RCC_Clocks;
int main(void)
{
//	RCC_GetClocksFreq(&RCC_Clocks);
     Init();             //各种东西的初始化配置
	
	/* 在这里添加你自己的程序 */
	while(1)
	{
//	LED1_TOGGLE;
//  delay_ms(500)
    Test();              //各种东西的运行测试
		
		
		
		
		//点灯测试
		GPIO_SetBits(GPIOG,LED_Pin);   //RM开发板高电平是熄灭
		delay_ms(500);
		GPIO_ResetBits(GPIOG,LED_Pin);
		delay_ms(200);
		

	}
}

