/*-------------------------------------------------------------------------------
文件名称：key.c
文件描述：按键相关功能函数。    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#include "key.h"
#include "delay.h"

KEY_RELEASE_Status __Key_release_flag;

/*-------------------------------------------------------------------------------
程序名称：KEY_Init
程序描述：按键引脚初始化，打开端口时钟，配置端口引脚，端口工作频率，端口输入模式 
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);													// 打开PA口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);													// 打开PE口时钟
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_4 | GPIO_Pin_5;											// PA4与PA5引脚设置	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;															// 端口速度
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;																// 端口模式，此为输入上拉模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);																				// 初始化对应的端口
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_15;																	// PE15引脚设置	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;															// 端口速度
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;																// 端口模式，此为输入上拉模式
	//GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;															 // 端口模式，此为输入下拉模式
	GPIO_Init(GPIOE, &GPIO_InitStructure);																				// 初始化对应的端口
}

/*-------------------------------------------------------------------------------
程序名称：KEY_Scan
程序描述：主要用于判断按键状态
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
u8 KEY_Scan(void)
{	 
	if((KEY1  == 1) || (KEY2 == 1) || (KEY3 == 1))
	{
		Delay_ms(10);																																// 去抖动 
		
		if(KEY1 == 1) return 1;
		else if(KEY2 == 1) return 2;
		else if(KEY3 == 1) return 3;
	}
	else
	{
		__Key_release_flag = REL_SET;																								// 按键释放标记
	}
	
	return 0;																																		  // 无按键按下
}
