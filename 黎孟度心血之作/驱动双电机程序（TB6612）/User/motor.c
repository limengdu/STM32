/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "motor.h"
#include "stm32f10x_exti.h"

/*******************************************************************************
* �� �� ��         : MOTOR_GPIO_Config
* ��������		   : ����GPIO��PB12/PB13/PB14/PB15
                     ���MOTOR��TIM2_CH3/TIM2_CH4
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void MOTOR_GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	//����һ��GPIO_InitTypeDef���͵Ľṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	//����GPIOB������ʱ��
															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	
	//ѡ��Ҫ���Ƶ�GPIOB����
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	//��������ģʽΪͨ���������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	//������������Ϊ50MHz
  	GPIO_Init(GPIOB, &GPIO_InitStructure);		  
	//���ÿ⺯������ʼ��GPIOB

	GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	//�͵�ƽ��ȷ����ʼ״̬�µ������ֹͣ״̬
	
	//GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14);
	//GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_15);
	//���������
}

/*******************************************************************************
* �� �� ��         : TIM2_GPIO_Config
* ��������		   : ����TIM2�������PWMʱ�õ���I/O
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
static void TIM2_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	//PCLK1����2��Ƶ����ΪTIM2��ʱ��Դ����72MHz

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* �� �� ��         : TIM2_Mode_Config
* ��������		   : ����TIM2�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
static void TIM2_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;

	/* PWM�źŵ�ƽ����ֵ */
	//u16 CCR1_Val = 500;        
	//u16 CCR2_Val = 800;
	u16 CCR3_Val = 0;
	u16 CCR4_Val = 0;
	 
	TIM_TimeBaseStructure.TIM_Period = 1000 ;       
	//ARR ����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	    
	//����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	
	//����ʱ�ӷ�Ƶϵ��������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	//���ϼ���ģʽ

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	   
	//��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
	//����ʱ������ֵС��CCR3_ValʱΪ�ߵ�ƽ

	TIM_OC3Init(TIM2, &TIM_OCInitStructure);//ʹ��ͨ��2
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	  
	//����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM

	TIM_OC4Init(TIM2, &TIM_OCInitStructure);//ʹ��ͨ��3
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM2, ENABLE);		// ʹ��TIM3���ؼĴ���ARR

	TIM_Cmd(TIM2, ENABLE);                  //ʹ�ܶ�ʱ��2	
}

/*******************************************************************************
* �� �� ��         : TIM2_PWM_Init
* ��������		   : TIM2 ���PWM�źų�ʼ����ֻҪ�����������
 *                   TIM2������ͨ���ͻ���PWM�ź����
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void TIM2_PWM_Init(void)
{
	TIM2_GPIO_Config(); //������źͶ�ʱ��ͨ��IO����
	TIM2_Mode_Config();	//����TIM2�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
}



