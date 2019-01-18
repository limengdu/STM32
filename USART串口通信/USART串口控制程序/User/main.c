#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"


int main (void)//主程序
{
	u8 a;
	u8 key;
	//初始化程序
	RCC_Configuration(); //时钟设置
	LED_Init();//LED初始化
	KEY_Init();//按键初始化
	USART1_Init(115200); //串口初始化（参数是波特率）

	//主循环
	while(1)
	{

		//查询方式接收，会出现延迟现象，可能需要发送多次数据才能实现命令，为了避免出现这种情况，我们可以打开串口的中断函数
		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) != RESET)//查询串口待处理标志位
			{ 
			a =USART_ReceiveData(USART1);//读取接收到的数据
			switch (a)
			{
				case '0':
					GPIO_SetBits(LED_PORT,GPIO_Pin_0); //LED1控制
					printf("%c:LED1 OFF ",a); //把收到的数据发送回电脑
					break;
				case '1':
					GPIO_ResetBits(LED_PORT,GPIO_Pin_0); //LED1控制
					printf("%c:LED1 ON ",a); //把收到的数据发送回电脑
					break;
				case '2':
					led2 = 1;                 //LED2控制
					printf("%c:LED2 OFF ",a); //把收到的数据发送回电脑
					break;
				case '3':
					led2 = 0;                 //LED2控制
					printf("%c:LED2 ON ",a); //把收到的数据发送回电脑
					break;
				default:
					break;
			}		  
		}

//按键控制(注意这里不可以放在中断服务函数中，因为没有发生中断的条件可以进入中断)
        key=KEY_Scan(0);   //扫描按键
		switch(key)
		{
			case KEY_UP: printf("KEY_UP");break;      //按下K_UP按键    点亮D2指示灯
			case KEY_DOWN: printf("KEY_DOWN");break;    //按下K_DOWN按键  熄灭D2指示灯
			case KEY_LEFT: printf("KEY_LEFT");break;    //按下K_LEFT按键  点亮D3指示灯
			case KEY_RIGHT: printf("KEY_RIGHT");break;   //按下K_RIGHT按键 熄灭D3指示灯
		}

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



