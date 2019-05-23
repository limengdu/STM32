/*-------------------------------------------------------------------------------
�ļ����ƣ�ccd.c
�ļ�����������CCDģ����ع��ܺ�����    
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "ccd.h"
#include "adc.h"
#include "delay.h"
#include "usart.h"

u16 ADV[128] = {0};    
extern u8 CCD_Threshold, CCD_Middle;

/*-------------------------------------------------------------------------------
�������ƣ�Dly_us
������������ͨ��ʱ
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void Dly_us(void)
{
	int ii;    
	for(ii = 0; ii < 10; ii++);      
}

/*-------------------------------------------------------------------------------
�������ƣ�RD_TSL
������������ȡ����CCDģ������
�����������
���ز�������
��    ע����
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
    Dly_us();  // �����ع�ʱ��
		Dly_us();  // �����ع�ʱ��
    ADV[tslp]=(Get_ADC(ADC_CH_x))>>4;
    ++tslp;
    TSL_CLK=1;
    Dly_us();
  }  
}

/*-------------------------------------------------------------------------------
�������ƣ�CCD_Init
��������������CCDģ���ʼ��
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void CCD_Init(void)
{    
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1, ENABLE);		 // ʹ��ADC1��GPIOCʱ��
	
	/* ���� PC0 ��Ϊģ������� */
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);																				 // PC0, ����ʱ������������
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);		

	ADC1_Mode_Configure();																												 // ADC1ģʽ����
}		

/*-------------------------------------------------------------------------------
�������ƣ�Find_CCD_Middle
��������������CCDȡ��ֵ
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void Find_CCD_Middle(void)
{ 
	static u16 i,j,Left,Right;
	static u16 value1_max,value1_min;

	value1_max = ADV[0];  																													// ��̬��ֵ�㷨����ȡ������Сֵ
	for(i = 5; i < 123; i++)   																											// ���߸�ȥ��5����
	{
		if(value1_max <= ADV[i])
		{
			value1_max = ADV[i];
		}
	}
	value1_min = ADV[0];  																													// ��Сֵ
	for(i=5; i<123; i++) 
	{
		if(value1_min >= ADV[i])
		value1_min = ADV[i];
	}
	CCD_Threshold = (value1_max+value1_min)/2;	  																	// ���������������ȡ����ֵ
	
	for(i = 5; i < 118; i++)   																											// Ѱ�����������
	{
		if((ADV[i] > CCD_Threshold) && (ADV[i+1] > CCD_Threshold) && (ADV[i+2] > CCD_Threshold) && (ADV[i+3] < CCD_Threshold) && (ADV[i+4] < CCD_Threshold) && (ADV[i+5] < CCD_Threshold))
		{	
			Left = i;
			break;	
		}
	}
	
	for(j = 118; j > 5; j--)																												// Ѱ���ұ�������
  {
		if((ADV[j] < CCD_Threshold) && (ADV[j+1] < CCD_Threshold) && (ADV[j+2] < CCD_Threshold) && (ADV[j+3] > CCD_Threshold) && (ADV[j+4] > CCD_Threshold) && (ADV[j+5] > CCD_Threshold))
		{	
		  Right = j;
		  break;	
		}
  }
	CCD_Middle = (Right+Left)/2;																										// ��������λ��
}
