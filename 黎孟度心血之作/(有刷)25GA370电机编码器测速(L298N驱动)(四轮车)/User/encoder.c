/* Includes ------------------------------------------------------------------*/
#include "encoder.h" 

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
  //ʹ�ܶ�ʱ��TIM3ͨ��3����GPIOB��ʱ��

  GPIO_InitStructure.GPIO_Pin =  ENCODER_TIM_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ENCODER_TIM_PORT, &GPIO_InitStructure);  
  //���ö�ʱ��ͨ��3����ģʽ����PB0
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
 * |_|       |__|      |___|     |____|    |_____|   |______|  |_______| |_________|
 *
 */
/*******************************************************************************
* �� �� ��         : ENCODER_TIMx_Configuration
* ��������		   : �������PWM�����벶���TIM3
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
static void ENCODER_TIMx_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef        TIM_ICInitStructure;

  //��ʼ��TIM3����
  ENCODER_TIM_APBxClock_FUN(ENCODER_TIM_CLK,ENABLE);
  //ʹ�ܶ�ʱ��TIM3ʱ��

  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_Period;
  //��ʱ����: 65535+1
	
  TIM_TimeBaseStructure.TIM_Prescaler = ENCODER_TIM_Prescaler;
  //����Ԥ��Ƶ��(72-1),�������Ƶ�ʣ�72MHz/(65535+1)/(72-1+1)
	
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
  //����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
	
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  //���ϼ���ģʽ
	
  TIM_TimeBaseInit(ENCODER_TIMx, &TIM_TimeBaseStructure);

  //��ʼ��TIM3���벶��
  TIM_ICInitStructure.TIM_Channel     = ENCODER_TIM_Channel_x;
/*�������벶���˲�������TIM_Channel_3
���벶���˲���ICF[3:0]������������ò���Ƶ�ʺ������˲������ȡ�
���У�fCK_INT�Ƕ�ʱ��������Ƶ�ʣ�fDTS�Ǹ���TIMx_CR1��CKD[1:0]��������ȷ���ġ�
�����˲�����һ���¼���������ɣ�����¼��N���¼�������һ����������䡣
Ҳ����˵����N�β�����������Ǹߵ�ƽ����˵������һ����Ч�Ĵ������ͻ�������벶׽�ж�
����������˵Ļ�����
�����Ϳ����˳���Щ�ߵ�ƽ�������8���������ڵ������źţ��Ӷ��ﵽ�˲������á�
*/

  TIM_ICInitStructure.TIM_ICPolarity  = ENCODER_TIM_ICPolarity;
  //�������벶׽���ԡ��������ز���

  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  //ӳ�䵽TI1��

  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  //�������벶���Ƶ����������Ƶ���������õ���ÿN���¼�����һ�β�׽��

  TIM_ICInitStructure.TIM_ICFilter    = 0x00;
  //IC1F=0000 ���������˲��� ���˲�
  
  TIM_ICInit(ENCODER_TIMx, &TIM_ICInitStructure);  
  
  TIMx_NVIC_Configuration();
  //����NVIC
  
  TIM_ITConfig(ENCODER_TIMx,ENCODER_TIM_IT_CCx, ENABLE);
  //��������ж� ,����CC1IE�����ж�
	
  TIM_Cmd(ENCODER_TIMx, ENABLE);
  //ʹ�ܶ�ʱ��  
}

/*******************************************************************************
* �� �� ��         : TIMx_DCmotor_ENCODER_Init
* ��������		   : TIM3ͨ��3���벶���ʼ��
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void TIMx_DCmotor_ENCODER_Init(void)
{
	ENCODER_TIMx_GPIO_Config();    //��ʱ��TIM3��������
	ENCODER_TIMx_Configuration();  //��ʱ��TIM3���벶������
}

