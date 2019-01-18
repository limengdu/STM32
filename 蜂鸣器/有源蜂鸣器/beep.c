#include "beep.h"

void BEEP_Init()                                         //蜂鸣器初始化函数
{
	GPIO_InitTypeDef GPIO_InitStructure;                 //定义结构体变量
	
	RCC_APB2PeriphClockCmd(BEEP_PORT_RCC,ENABLE);        //开启时钟

    GPIO_InitStructure.GPIO_Pin   = BEEP_PIN;            //设置引脚号
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;    //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //设置输出频率为50MHz
	GPIO_Init(BEEP_PORT,&GPIO_InitStructure);            //初始化引脚
	
	GPIO_SetBits(BEEP_PORT,BEEP_PIN);                    //给蜂鸣器引脚输出高电平，确保初始状态蜂鸣器处于截止状态
}







