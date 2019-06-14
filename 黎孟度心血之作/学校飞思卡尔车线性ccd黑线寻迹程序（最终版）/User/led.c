/*-------------------------------------------------------------------------------
文件名称：led.c
文件描述：用于配置LED的功能函数。    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#include "led.h"
#include "delay.h"

/*-------------------------------------------------------------------------------
函数名称：LED_Init
函数描述：初始化LED相关端口，打开端口时钟，配置端口输出。
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);			// 使能PA、PD端口时钟
	
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;																			// PA12 引脚设置
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;																	// 端口速度(MAX)			
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;																	// 端口模式，此为输出推挽模式
  GPIO_Init(GPIOA, &GPIO_InitStructure);																						// 初始化对应PA端口
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;																				// PD3 引脚设置
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;																	// 端口速度(MAX)			
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;																	// 端口模式，此为输出推挽模式
  GPIO_Init(GPIOD, &GPIO_InitStructure);																						// 初始化对应PD端口
}

/*-------------------------------------------------------------------------------
函数名称：LED_State
函数描述：LED指示灯，用于MCU与代码运行情况监控检测。
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void LED_State(void)
{
	LED1_ON;																																					// MCU与代码运行正常，状态指示灯 1开
	LED2_OFF;
	
	Delay_ms(1000);																																		// 用于LED2 延时启动测试
	
	LED2_ON;																																					// MCU与代码运行正常，状态指示灯 2开
}
