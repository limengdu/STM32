/*-------------------------------------------------------------------------------
文件名称：ccd.c
文件描述：线性CCD模块相关功能函数。    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#include "ccd.h"
#include "adc.h"
#include "delay.h"
#include "usart.h"

u16 ADV[128] = {0};    
extern u8 CCD_Threshold, CCD_Middle;

/*-------------------------------------------------------------------------------
函数名称：Dly_us
函数描述：普通延时
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void Dly_us(void)
{
	int ii;    
	for(ii = 0; ii < 10; ii++);      
}

/*-------------------------------------------------------------------------------
函数名称：RD_TSL
函数描述：读取线性CCD模块数据
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void RD_TSL(void) 
{
	u8 i=0,tslp=0;
	
  TSL_CLK=1;
  TSL_SI=0; 
  Dly_us();
      
  TSL_SI=1; 
  TSL_CLK=0;
  Dly_us();
      
  TSL_CLK=1;
  TSL_SI=0;
  Dly_us(); 
  for(i = 0; i < 128; i++)
  { 
		TSL_CLK=0; 
    Dly_us();  // 调节曝光时间
		Dly_us();  // 调节曝光时间
    ADV[tslp]=(Get_ADC(ADC_CH_x))>>4;
    ++tslp;
    TSL_CLK=1;
    Dly_us();
  }  
}

/*-------------------------------------------------------------------------------
函数名称：CCD_Init
函数描述：线性CCD模块初始化
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void CCD_Init(void)
{    
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1, ENABLE);		 // 使能ADC1和GPIOC时钟
	
	/* 配置 PC0 作为模拟输入口 */
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);																				 // PC0, 输入时不用设置速率
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);		

	ADC1_Mode_Configure();																												 // ADC1模式配置
}		

/*-------------------------------------------------------------------------------
函数名称：Find_CCD_Middle
函数描述：线性CCD取中值
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void Find_CCD_Middle(void)
{ 
	static u16 i,j,Left,Right;
	static u16 value1_max,value1_min;

	value1_max = ADV[0];  																													// 动态阈值算法，读取最大和最小值
	for(i = 5; i < 123; i++)   																											// 两边各去掉5个点
	{
		if(value1_max <= ADV[i])
		{
			value1_max = ADV[i];
		}
	}
	value1_min = ADV[0];  																													// 最小值
	for(i=5; i<123; i++) 
	{
		if(value1_min >= ADV[i])
		value1_min = ADV[i];
	}
	CCD_Threshold = (value1_max+value1_min)/2;	  																	// 计算出本次中线提取的阈值
	
	for(i = 5; i < 118; i++)   																											// 寻找左边跳变沿
	{
		if((ADV[i] > CCD_Threshold) && (ADV[i+1] > CCD_Threshold) && (ADV[i+2] > CCD_Threshold) && (ADV[i+3] < CCD_Threshold) && (ADV[i+4] < CCD_Threshold) && (ADV[i+5] < CCD_Threshold))
		{	
			Left = i;
			break;	
		}
	}
	
	for(j = 118; j > 5; j--)																												// 寻找右边跳变沿
  {
		if((ADV[j] < CCD_Threshold) && (ADV[j+1] < CCD_Threshold) && (ADV[j+2] < CCD_Threshold) && (ADV[j+3] > CCD_Threshold) && (ADV[j+4] > CCD_Threshold) && (ADV[j+5] > CCD_Threshold))
		{	
		  Right = j;
		  break;	
		}
  }
	CCD_Middle = (Right+Left)/2;																										// 计算中线位置
}
