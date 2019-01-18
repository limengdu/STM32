/* Includes ------------------------------------------------------------------*/
#include "SG90.h"

/*******************************************************************************
* �� �� ��         : SG90_Init
* ��������		   : ����ӿڳ�ʼ��
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void SG90_Init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);       
    GPIO_InitStructure.GPIO_Pin = SE_OUT;             //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //ѡ��IO�ӿڹ�����ʽ       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶ�
	GPIO_Init(SE_PORT, &GPIO_InitStructure);
	GPIO_WriteBit(SE_PORT,SE_OUT,(BitAction)(0));     //�ӿ����
}

/*******************************************************************************
* �� �� ��         : SG90_angle
* ��������		   : ����Ƕȿ������ã�����ֵ0��180����Ӧ�Ƕ�0��180��
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void SG90_angle(u8 a)
{
	u8 b=100;                                     //�Ƕ�У��ƫ����
	                            //ÿ������ĽǶ�ƫ�����������һ������Ҫ�Լ�����
	GPIO_WriteBit(SE_PORT,SE_OUT,(BitAction)(1)); //�ӿ����
	delay_us(500+a*10+b);                         //��ʱ
	GPIO_WriteBit(SE_PORT,SE_OUT,(BitAction)(0)); //�ӿ����
	delay_us(19500-a*10-b);                       //��ʱ
} 


