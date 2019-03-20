/*******************************************************************************
模板制作：  华南理工大学广州学院野狼队
程序名：	PWM驱动舵机程序
编写人：	黎孟度
编写时间：	2019年1月16日
硬件支持：	STM32F103ZET6　  

修改日志：　　
1-	
	
说明：
 # 本程序是基于STM32F103ZET6开发板的硬件基础上编写的，移植需了解硬件接口差异。
 # 本模板加载了STM32F103内部的RCC时钟设置，并加入了利用滴答定时器的延时函数。
 # 本模板可以使用两种方式来操作舵机转动，一种是使用TIM3输出PWM驱动舵机
   （调用TIM_SetCompare3函数），缺点是转动角度需要根据比例自己计算；
   第二种方式是使用滴答定时器延时实现PWM输出，由于周期内占空的时间是直接与角度
   挂钩的，因此直接用SG90_angle函数可以实现精确角度转动，但缺点是不能在该函数后
   面加入其它延时程序，否则会影响SG90_angle中的PWM周期。
 # 可根据自己的需要增加或删减。
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "SG90.h"
#include "pwm.h"

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 配置有关器件初始化、实现舵机转动
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
int main (void)               //主程序
{
	delay_ms(500);            //上电时等待其他器件就绪
	RCC_Configuration();      //系统时钟初始化 
    SG90_Init();              //舵机接口初始化
	TIM3_PWM_Init(59999,23); 
	//设置频率为50Hz，公式为：溢出时间Tout（单位秒）=(arr+1)(psc+1)/Tclk	 
	//20MS = (59999+1)*(23+1)/72000000
    //Tclk为通用定时器的时钟，如果APB1没有分频，则就为系统时钟，72MHZ
    //PWM时钟频率= 50HZ (20ms)，设置自动装载值60000,预分频系数24

	while(1)
		{
			//第一种方法实现转动
//		  TIM_SetCompare3(TIM3,1500); //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
//		  TIM_SetCompare3(TIM3,3000); //改变比较值TIM3->CCR2达到调节占空比的效果
//		  TIM_SetCompare3(TIM3,4500); //改变比较值TIM3->CCR2达到调节占空比的效果
//		  TIM_SetCompare3(TIM3,7500); //改变比较值TIM3->CCR2达到调节占空比的效果
			
			//第二种方法实现转动
//			SG90_angle(0);
//			SG90_angle(30);
			SG90_angle(60);
//			SG90_angle(90);
		}
}

/****************** (C) COPYRIGHT 2019 黎孟度心血之作 **************************
******************************END OF FILE**************************************/

/*
【变量定义】
u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8      a; //定义8位无符号变量a
vu32    a; //定义易变的32位无符号变量a
vu16    a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32    a; //定义只读的32位无符号变量a
uc16    a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a

delay_us(1); //延时1微秒
delay_ms(1); //延时1毫秒
delay_s(1); //延时1秒

*/



