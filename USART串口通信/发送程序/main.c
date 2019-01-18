#include "stm32f10x.h" 
#include "SysTick.h"
#include "usart.h"


int main (void)//主程序
{
	u8 a=7,b=8;
	//初始化程序
	SysTick_Init(72);

	USART1_Init(115200); //串口初始化（参数是波特率）

	//主循环
	while(1)
	{
		/* 发送方法1 */
		USART_SendData(USART1 , 0x55); //发送单个数值
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); //检查发送中断标志位

		/* 发送方法2 */
//		printf("STM32F103 "); //纯字符串发送数据到串口

//		printf("STM32 %d %d ",a,b); //纯字符串和变量发送数据到串口,a符号变量
		 
		/* 发送方法3 */
//		USART1_printf("STM32 %d %d ",a,b);

        delay_ms(1000); //延时
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

#define ONE  1   //宏定义

delay_us(1); //延时1微秒
delay_ms(1); //延时1毫秒
delay_s(1); //延时1秒

*/



