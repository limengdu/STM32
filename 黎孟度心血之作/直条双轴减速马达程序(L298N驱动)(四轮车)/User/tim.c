/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/*******************************************************************************
* �� �� ��         : GPIOCLK_Init
* ��������		   : ʹ������GPIOʱ��
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void GPIOCLK_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG , ENABLE);
}



/*******************************************************************************
* �� �� ��         : NVIC_TIM2Configuration
* ��������		   : NVIC�ж�����
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
static void NVIC_TIM2Configuration(void)
{ 
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            //�����ж���TIM2
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         //��Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //ʹ��NVIC

    NVIC_Init(&NVIC_InitStructure);                            //��ʼ��NVIC
}

/*******************************************************************************
* �� �� ��         : TIM2_Init
* ��������		   : ��ʱ��TIM2��ʼ��
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void TIM2_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//����ʱ��

    TIM_TimeBaseStructure.TIM_Period = (100 - 1);
	//�����Զ�װ�صļ���ֵCNT��������0��ʼ������Ϊ1ms
	
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);
	//����Ԥ��Ƶϵ����������Ϊ0ʱ��ʾ����Ƶ����Ҫ��1
	
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	//���÷�Ƶϵ��

    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//�������ϼ���ģʽ
	
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//��ʼ����ʱ��2

    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	//���TIM2����жϱ�־

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//������ж�

    TIM_Cmd(TIM2, ENABLE);  
	//������ʹ�ܣ���ʼ����

    NVIC_TIM2Configuration();
	//NVIC��ʼ��
}




