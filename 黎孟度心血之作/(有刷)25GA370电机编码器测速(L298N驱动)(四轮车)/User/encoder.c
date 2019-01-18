/* Includes ------------------------------------------------------------------*/
#include "encoder.h" 

__IO uint32_t CaptureNumber = 0;

/*******************************************************************************
* �� �� ��         : ENCODER_TIMx_GPIO_Config
* ��������		   : ��ʼ����ʱ��TIM3����
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
static void ENCODER_TIMx_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  ENCODER_TIM_GPIO_APBxClock_FUN(ENCODER_TIM_GPIO_CLK, ENABLE); 
  //ʹ�ܶ�ʱ��TIM3ͨ��3����GPIOʱ��

  GPIO_InitStructure.GPIO_Pin =  ENCODER_TIM_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ENCODER_TIM_PORT, &GPIO_InitStructure);  
  //���ö�ʱ��ͨ��3����ģʽ
}

/*******************************************************************************
* �� �� ��         : TIMx_NVIC_Configuration
* ��������		   : ����Ƕ�������жϿ�����NVIC
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
static void TIMx_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  //ѡ���ж����ȼ�������Ϊ2����ռʽ���ȼ���2�������ȼ�

  NVIC_InitStructure.NVIC_IRQChannel = ENCODER_TIMx_IRQn;  
  //����TIM3_IRQ�ж�Ϊ�ж�Դ
	
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  //������ռʽ���ȼ�Ϊ0
	
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  //���������ȼ�Ϊ2
	
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  //ʹ���ⲿ�ж�ͨ��
	
  NVIC_Init(&NVIC_InitStructure);
}

/*
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT ���¼���
 *                    TIMx_CCR(��ƽ�����仯)
 * �ź�����=(TIMx_ARR +1 ) * ʱ������
 * ռ�ձ�=TIMx_CCR/(TIMx_ARR +1)
 *    _______    ______     _____      ____       ___        __         _
 * |_|       |__|      |___|     |____|    |_____|   |______|  |_______| |________|
 *
 */
/*******************************************************************************
* �� �� ��         : ENCODER_TIMx_Configuration
* ��������		   : ����TIMx�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
static void ENCODER_TIMx_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef        TIM_ICInitStructure;

  /* ʹ�ܶ�ʱ��ʱ�� */
  ENCODER_TIM_APBxClock_FUN(ENCODER_TIM_CLK,ENABLE);
  /* ��ʱ����������ʼ�� */		 
  /* ��ʱ����: ENCODER_TIM_Period+1 */
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_Period; 
  /* ����Ԥ��Ƶ��ENCODER_TIM_Prescaler,�������Ƶ�ʣ�72MHz/(ENCODER_TIM_Prescaler+1)/(ENCODER_TIM_Period+1) */
  TIM_TimeBaseStructure.TIM_Prescaler = ENCODER_TIM_Prescaler;
  /* ����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���) */
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
  /* ���ϼ���ģʽ */
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(ENCODER_TIMx, &TIM_TimeBaseStructure);

  /* ��ʼ��TIM5���벶����� */
  /* CC1S=01 	ѡ������� IC1ӳ�䵽TI1�� */
	TIM_ICInitStructure.TIM_Channel     = ENCODER_TIM_Channel_x;
  /* �����ز��� */
	TIM_ICInitStructure.TIM_ICPolarity  = ENCODER_TIM_ICPolarity;	
  /* ӳ�䵽TI1�� */
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
  /* ���������Ƶ,����Ƶ  */
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	           
  /* IC1F=0000 ���������˲��� ���˲� */
	TIM_ICInitStructure.TIM_ICFilter    = 0x00;                         
	TIM_ICInit(ENCODER_TIMx, &TIM_ICInitStructure);  
  
  /* ����NVIC */
  TIMx_NVIC_Configuration();
  
  /* ��������ж� ,����CC1IE�����ж�	 */
  TIM_ITConfig(ENCODER_TIMx,ENCODER_TIM_IT_CCx, ENABLE);
	
  /* ʹ�ܶ�ʱ�� */
  TIM_Cmd(ENCODER_TIMx, ENABLE);							
}


/**
  * ��������: TIMxͨ��1���벶���ʼ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void TIMx_DCmotor_ENCODER_Init(void)
{
	ENCODER_TIMx_GPIO_Config();
	ENCODER_TIMx_Configuration();	
}

void ENCODER_TIMx_IRQHandler(void)
{
 	if(TIM_GetITStatus(ENCODER_TIMx, ENCODER_TIM_IT_CCx) == SET )     //�����ж�
	{
     /* Clear TIM3 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(ENCODER_TIMx, ENCODER_TIM_IT_CCx);
    CaptureNumber++;  // ÿ��һ�������ؼ�һ
	}
}


