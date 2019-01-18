#include "stm32f10x.h"
#include "SysTick.h"
#include "beep.h"


int main (void)                       //主程序
{
	SysTick_Init(72);

	BEEP_Init();                      //蜂鸣器初始化

	//主循环
	while(1)
	{
		BEEP_1();                     //蜂鸣器音1 
	}
}


/*

【变量定义】
u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8     a; //定义8位无符号变量a
vu32     a; //定义易变的32位无符号变量a
vu16     a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32     a; //定义只读的32位无符号变量a
uc16     a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a


delay_us(1); //延时1微秒
delay_ms(1); //延时1毫秒
delay_s(1); //延时1秒

*/



