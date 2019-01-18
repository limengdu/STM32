#include "beep.h"
#include "SysTick.h"

void BEEP_Init(void)                                     //蜂鸣器的接口初始化
{ 
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    GPIO_InitStructure.GPIO_Pin = BEEP_PIN;              //选择端口号                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //选择IO接口工作方式       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //设置IO接口速度（2/10/50MHz）    
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);	
	
	GPIO_SetBits(BEEP_PORT,BEEP_PIN);                    //蜂鸣器接口输出高电平1		
}

void BEEP_1(void)                                        //蜂鸣器响一声
{ 
	u16 i;
	for(i=0;i<200;i++)
	{
		GPIO_ResetBits(BEEP_PORT, BEEP_PIN);             //蜂鸣器接口输出0
		delay_us(500);                                   //延时		
		GPIO_SetBits(BEEP_PORT, BEEP_PIN);               //蜂鸣器接口输出高电平1
		delay_us(500);                                   //延时		
	}
}

 
/*
选择IO接口工作方式：
GPIO_Mode_AIN 模拟输入
GPIO_Mode_IN_FLOATING 浮空输入
GPIO_Mode_IPD 下拉输入
GPIO_Mode_IPU 上拉输入
GPIO_Mode_Out_PP 推挽输出
GPIO_Mode_Out_OD 开漏输出
GPIO_Mode_AF_PP 复用推挽输出
GPIO_Mode_AF_OD 复用开漏输出
*/
