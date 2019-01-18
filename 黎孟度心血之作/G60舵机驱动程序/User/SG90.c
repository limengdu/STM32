/* Includes ------------------------------------------------------------------*/
#include "SG90.h"

/*******************************************************************************
* 函 数 名         : SG90_Init
* 函数功能		   : 舵机接口初始化
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void SG90_Init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);       
    GPIO_InitStructure.GPIO_Pin = SE_OUT;             //选择端口号（0~15或all）                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //选择IO接口工作方式       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度
	GPIO_Init(SE_PORT, &GPIO_InitStructure);
	GPIO_WriteBit(SE_PORT,SE_OUT,(BitAction)(0));     //接口输出
}

/*******************************************************************************
* 函 数 名         : SG90_angle
* 函数功能		   : 舵机角度控制设置（参数值0～180）对应角度0～180度
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void SG90_angle(u8 a)
{
	u8 b=100;                                     //角度校正偏移量
	                            //每个舵机的角度偏移量情况都不一样，需要自己来调
	GPIO_WriteBit(SE_PORT,SE_OUT,(BitAction)(1)); //接口输出
	delay_us(500+a*10+b);                         //延时
	GPIO_WriteBit(SE_PORT,SE_OUT,(BitAction)(0)); //接口输出
	delay_us(19500-a*10-b);                       //延时
} 


