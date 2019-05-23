/*-------------------------------------------------------------------------------
�ļ����ƣ�adc.c
�ļ�������ADC��ع��ܺ�����      
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "adc.h"
#include "delay.h"

/*-------------------------------------------------------------------------------
�������ƣ�ADC1_GPIO_Configure
����������ADC1�Ĺ���ģʽ���ã�����ת��ģʽ��
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void ADC1_Mode_Configure(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	/* ADC1 configuration */
	ADC_DeInit(ADC1);																															// ��λADC1
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); 																						// ����ADCʱ�ӣ�ΪPCLK2��6��Ƶ����12MHz������ܳ���14MHz�����򽫵���ADC׼ȷ���½�
	
	ADC_InitStructure.ADC_Mode 							 = ADC_Mode_Independent;							// ����ADCģʽ
	ADC_InitStructure.ADC_ScanConvMode 			 = DISABLE; 	 												// ��ֹɨ��ģʽ��ɨ��ģʽ���ڶ�ͨ���ɼ�
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;														// ����ת��ģʽ������������ת��ģʽ��
	ADC_InitStructure.ADC_ExternalTrigConv 	 = ADC_ExternalTrigConv_None;					// ��ʹ���ⲿ����ת����ѡ���������ģʽ��
	ADC_InitStructure.ADC_DataAlign 				 = ADC_DataAlign_Right; 							// �ɼ������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel 			 = 1;	 																// Ҫת����ͨ����Ŀ1
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1, ENABLE);																												// ʹ�� ADC1  
	
	ADC_ResetCalibration(ADC1);																										// ��λУ׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));																		// �ȴ�У׼�Ĵ�����λ���
	
	ADC_StartCalibration(ADC1);																										// ADC1 У׼
	while(ADC_GetCalibrationStatus(ADC1));																				// �ȴ� ADC1 У׼���
}

/*-------------------------------------------------------------------------------
�������ƣ�Get_ADC
������������ȡADCת������
���������ѡ��ADCͨ��
���ز���������ADC������ת�����
��    ע����
---------------------------------------------------------------------------------*/
u16 Get_ADC(u8 ch)
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);							// ����ADC1��ͨ��10�Ĳ���ʱ��Ϊ239.5���������ڣ���߲���ʱ�������߾�ȷ�ȣ����������˳��ֵΪ1�������У�ת����Ϊ1
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);																				// ����û�в����ⲿ����������ʹ���������ADCת��

	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));																// �ȴ�ת������
	return ADC_GetConversionValue(ADC1);																					// �������һ��ADC1�������ת�����
}

/*-------------------------------------------------------------------------------
�������ƣ�Get_ADC_Average
����������ADCƽ��ת��ֵ
���������ȡ������
���ز�������
��    ע����
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


