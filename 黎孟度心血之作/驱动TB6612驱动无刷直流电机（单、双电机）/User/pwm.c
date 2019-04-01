/* Includes ------------------------------------------------------------------*/
#include "pwm.h" 

/*******************************************************************************
* �� �� ��         : PWM_GPIO_Config
* ��������		   : ����TIMx�������PWMʱ�õ���I/O
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void PWM_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ʹ�ܶ�ʱ��ʼ�� */
	DCMOTOR_BRUSH_TIM_APBxClock_FUN(DCMOTOR_BRUSH_TIM_CLK, ENABLE);

	/* ʹ�ܶ�ʱ��ͨ������GPIOʱ�� */
	DCMOTOR_BRUSH_TIM_GPIO_APBxClock_FUN(DCMOTOR_BRUSH_TIM_GPIO_CLK|
	                                     RCC_APB2Periph_AFIO, ENABLE); 

    /* ���ö�ʱ��ͨ��1�������ģʽ�������������ģʽ */
	GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DCMOTOR_BRUSH_TIM_CH1_PORT, &GPIO_InitStructure);
	
	/* ���ö�ʱ������ͨ��1�������ģʽ*/
	GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH1N_PIN;
	GPIO_Init(DCMOTOR_BRUSH_TIM_CH1N_PORT, &GPIO_InitStructure);
}


/*
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT ���¼���
 *                    TIMx_CCR(��ƽ�����仯)
 * �ź�����=(TIMx_ARR +1 ) * ʱ������
 * ռ�ձ�=TIMx_CCR/(TIMx_ARR +1)
 */

/*******************************************************************************
* �� �� ��         : PWM_TIMx_Config
* ��������		   : ����TIMx�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void PWM_TIMx_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* ��ʱ����������ʼ�� */		
	/* ����ʱ����0������3600-1����Ϊ3600�Σ�Ϊһ����ʱ���� */
	TIM_TimeBaseStructure.TIM_Period = 3600-1;   
	/* ����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz,�������Ƶ�ʣ�72MHz/3600=20KHz */
	/* ͬһ����ʱ���Ĳ�ͬͨ��PWM��Ƶ��ֻ������ͬ�ģ���ͬͨ����������Ϊ��ͬ��ռ�ձ� */
	TIM_TimeBaseStructure.TIM_Prescaler = 1;
	/* ����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���) */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
	/* ���ϼ���ģʽ */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	/* �ظ������� */
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(DCMOTOR_BRUSH_TIMx, &TIM_TimeBaseStructure);

	/* ��ʱ�����ͨ��1ģʽ���� */
	/* ģʽ���ã�PWMģʽ1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	/* ���״̬���ã�ʹ����� */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	/* ����ͨ�����״̬���ã�ʹ����� */
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	/* ��������ֵ�������������������ֵʱ����ƽ�������� */
	TIM_OCInitStructure.TIM_Pulse = 1800-1;
	/* ����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ */
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	/* ��ʼ����ʱ��ͨ��1���PWM */
	TIM_OC1Init(DCMOTOR_BRUSH_TIMx, &TIM_OCInitStructure);
	/* ��ʱ���Ƚ����ͨ��1Ԥװ�����ã�ʹ��Ԥװ�� */
	TIM_OC1PreloadConfig(DCMOTOR_BRUSH_TIMx, TIM_OCPreload_Enable);
  
	/* ʹ�ܶ�ʱ�����ؼĴ���ARR */
	TIM_ARRPreloadConfig(DCMOTOR_BRUSH_TIMx, ENABLE);

	/* ʹ�ܶ�ʱ�� */
	TIM_Cmd(DCMOTOR_BRUSH_TIMx, ENABLE);

	/* TIM�����ʹ�� */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}


/*******************************************************************************
* �� �� ��         : TIMx_PWM_Init
* ��������		   : TIMx���PWM�źų�ʼ��
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void TIMx_PWM_Init(void)
{
	PWM_GPIO_Config();
	PWM_TIMx_Config();
}

