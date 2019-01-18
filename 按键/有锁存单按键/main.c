//该模板实现的操作是：按一次按键，灯亮，再按一次按键，灯灭
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "key.h"


int main()
{
	SysTick_Init(72);
	LED_Init();
	KEY_Init();
	
	while(1)
	{
		if(GPIO_ReadInputDataBit(KEY_PORT,GPIO_Pin_X)==0)        //修改：读取按键X引脚电平状态，当按键按下时
		{
			delay_ms(20);	                                     //按键机械抖动时间约10~20ms，这里延时20ms来消抖
			if(GPIO_ReadInputDataBit(KEY_PORT,GPIO_Pin_X)==1)    //修改：消抖结束之后，再判断按键X引脚电平状态，当松开按键时，执行以下操作
			{
				PXout(X)=!PXout(X);                              //修改：这里表示取反操作，当灯之前为低电平状态则变为高电平；当灯之前为高电平状态则变为低电平
			}
		}	
	}
}
