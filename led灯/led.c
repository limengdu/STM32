#include "led.h"

void LED_Init()                                         //LED初始化函数
{
	GPIO_InitTypeDef GPIO_InitStructure;                //定义结构体变量
	
	RCC_APB2PeriphClockCmd(LED_PORT_RCC,ENABLE);        //开启时钟

    GPIO_InitStructure.GPIO_Pin   = LED_PIN;            //设置引脚号
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;   //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //设置输出频率为50MHz
	GPIO_Init(LED_PORT,&GPIO_InitStructure);            //初始化引脚
	
	GPIO_SetBits(LED_PORT,LED_PIN);                     //给LED引脚输出高电平，确保初始状态熄灭所有灯
}







