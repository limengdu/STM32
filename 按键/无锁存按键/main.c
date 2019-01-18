#include "key.h"


int main()
{
	KEY_Init();
	
	while(1)
	{
		                                                     //无锁存版本
		if(GPIO_ReadInputDataBit(KEY_PORT,KEY_PORT_PIN)==1)  //判断按键电平是否为高电平
			XXX;                                             //修改：当检测按键电平为高电平时（即未按下按键），执行XXX操作
		else XXX;                                            //修改：否则（即按键按下）执行XXX操作
			
	}
}
