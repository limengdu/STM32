/*-------------------------------------------------------------------------------
文件名称：adc.c
文件描述：ADC相关功能函数。      
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#include "adc.h"
#include "delay.h"

/*-------------------------------------------------------------------------------
函数名称：ADC1_GPIO_Configure
函数描述：ADC1的工作模式配置（单次转换模式）
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void ADC1_Mode_Configure(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	/* ADC1 configuration */
	ADC_DeInit(ADC1);																															// 复位ADC1
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); 																						// 配置ADC时钟，为PCLK2的6分频，即12MHz，最大不能超过14MHz，否则将导致ADC准确度下降
	
	ADC_InitStructure.ADC_Mode 							 = ADC_Mode_Independent;							// 独立ADC模式
	ADC_InitStructure.ADC_ScanConvMode 			 = DISABLE; 	 												// 禁止扫描模式，扫描模式用于多通道采集
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;														// 单次转换模式（不开启连续转换模式）
	ADC_InitStructure.ADC_ExternalTrigConv 	 = ADC_ExternalTrigConv_None;					// 不使用外部触发转换（选择软件触发模式）
	ADC_InitStructure.ADC_DataAlign 				 = ADC_DataAlign_Right; 							// 采集数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel 			 = 1;	 																// 要转换的通道数目1
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1, ENABLE);																												// 使能 ADC1  
	
	ADC_ResetCalibration(ADC1);																										// 复位校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));																		// 等待校准寄存器复位完成
	
	ADC_StartCalibration(ADC1);																										// ADC1 校准
	while(ADC_GetCalibrationStatus(ADC1));																				// 等待 ADC1 校准完成
}

/*-------------------------------------------------------------------------------
函数名称：Get_ADC
函数描述：获取ADC转换数据
输入参数：选择ADC通道
返回参数：返回ADC的数据转换结果
备    注：无
---------------------------------------------------------------------------------*/
u16 Get_ADC(u8 ch)
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);							// 配置ADC1的通道10的采样时间为239.5个采样周期（提高采样时间可以提高精确度），规则采样顺序值为1，即序列（转换）为1
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);																				// 由于没有采用外部触发，所以使用软件触发ADC转换

	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));																// 等待转换结束
	return ADC_GetConversionValue(ADC1);																					// 返回最近一次ADC1规则组的转换结果
}

/*-------------------------------------------------------------------------------
函数名称：Get_ADC_Average
函数描述：ADC平均转换值
输入参数：取样次数
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
u16 Get_ADC_Average(u8 times)
{
	u32 temp_val = 0;
	u8 t;
	for(t = 0; t < times; t++)
	{
		temp_val += Get_ADC(ADC_CH_x);
		Delay_ms(5);
	}
	return temp_val/times;
}


