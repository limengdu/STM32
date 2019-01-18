#include "key.h"
#include "stm32f10x.h"

/*******************************************************************************
* 函 数 名         : KEY_Init
* 函数功能		   : 按键初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                 //定义结构体变量	
	RCC_APB2PeriphClockCmd(GPIO_KEY_RCC,ENABLE);         //开启按键所在的时钟

	GPIO_InitStructure.GPIO_Pin = KEY_UP_PIN;	         //这里设置复位按键的引脚
	GPIO_InitStructure.GPIO_Mode = KEY_SET_MODE;         //复位按键一般接在高电平上，故输入模式选择下拉输入 
	
	GPIO_InitStructure.GPIO_Pin=KEY_PORT_PIN;	         //选择你要设置的按键所在的IO口
	GPIO_InitStructure.GPIO_Mode=KEY_MODE;               //设置按键输入模式（上拉模式）

	GPIO_Init(KEY_PORT,&GPIO_InitStructure);		     //初始化GPIO
	
}

u8 KEY_Scan(u8 mode)                                     //按键扫描函数
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







