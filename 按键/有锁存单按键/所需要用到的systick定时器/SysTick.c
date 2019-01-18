#include "SysTick.h"

static u8  fac_us=0;							//us��ʱ������			   
static u16 fac_ms=0;							//ms��ʱ������
static u32 fac_s=0;               //s��ʱ������

//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪAHBʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��Ƶ��

void SysTick_Init(u8 SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	fac_us=SYSCLK/8;					
	fac_ms=(u16)fac_us*1000;
  fac_s=(u32)fac_ms*1000;	
}								    

void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//ʱ�����	  		 
	SysTick->VAL=0x00;        					//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;      					 //��ռ�����	 
}

void delay_ms(u16 nms)
{	 		  	  

  while( nms-- != 0)
	{
		delay_us(1000);	//����1000΢�����ʱ
	}	
	
} 

void delay_s(u16 nns)
{
  while( nns-- != 0)
	{
		delay_ms(1000);	//����1000�������ʱ
	}	
}
