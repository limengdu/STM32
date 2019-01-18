/**
  ******************************************************************************
  * �ļ�����: bsp_DCmotor_brush_TIM.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2015-10-04
  * ��    ��: ֱ����ˢ�������ʵ��
  ******************************************************************************
  * ˵����
  * ����������Ӳʯstm32������YS-F1Proʹ�á�
  * 
  * �Ա���
  * ��̳��http://www.ing10bbs.com
  * ��Ȩ��ӲʯǶ��ʽ�����Ŷ����У��������á�
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "tim.h" 

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/
/**
  * ��������: ����TIMx�������PWMʱ�õ���I/O
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
static void DCMOTOR_BRUSH_TIMx_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* ʹ�ܶ�ʱ��ʼ�� */
	DCMOTOR_BRUSH_TIM_APBxClock_FUN(DCMOTOR_BRUSH_TIM_CLK, ENABLE);

  /* ʹ�ܶ�ʱ��ͨ������GPIOʱ�� */
  DCMOTOR_BRUSH_TIM_GPIO_APBxClock_FUN(DCMOTOR_BRUSH_TIM_GPIO_CLK|RCC_APB2Periph_AFIO, ENABLE); 

  /* ���ö�ʱ��ͨ��1�������ģʽ�������������ģʽ */
  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DCMOTOR_BRUSH_TIM_CH1_PORT, &GPIO_InitStructure);

//  /* ���ö�ʱ��ͨ��2�������ģʽ */
//  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH2_PIN;
//  GPIO_Init(DCMOTOR_BRUSH_TIM_CH2_PORT, &GPIO_InitStructure);

//  /* ���ö�ʱ��ͨ��3�������ģʽ */
//  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH3_PIN;
//  GPIO_Init(DCMOTOR_BRUSH_TIM_CH3_PORT, &GPIO_InitStructure);
  
  /* ���ö�ʱ������ͨ��1�������ģʽ */
  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH1N_PIN;
  GPIO_Init(DCMOTOR_BRUSH_TIM_CH1N_PORT, &GPIO_InitStructure);
  
//  /* ���ö�ʱ������ͨ��2�������ģʽ */
//  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH2N_PIN;
//  GPIO_Init(DCMOTOR_BRUSH_TIM_CH2N_PORT, &GPIO_InitStructure);
//  
//  /* ���ö�ʱ������ͨ��3�������ģʽ */
//  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH3N_PIN;
//  GPIO_Init(DCMOTOR_BRUSH_TIM_CH3N_PORT, &GPIO_InitStructure);  
}

/**
  * ��������: ����TIMx�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
/*
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT ���¼���
 *                    TIMx_CCR(��ƽ�����仯)
 * �ź�����=(TIMx_ARR +1 ) * ʱ������
 * ռ�ձ�=TIMx_CCR/(TIMx_ARR +1)
 */
static void DCMOTOR_BRUSH_TIMx_Configuration(void)
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
  
//  /* ��ʱ�����ͨ��2ģʽ���� */
//  /* ����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM */
//  TIM_OCInitStructure.TIM_Pulse = 1800-1;
//  /* ��ʼ����ʱ��ͨ��2���PWM */
//  TIM_OC2Init(DCMOTOR_BRUSH_TIMx, &TIM_OCInitStructure);
//  /* ��ʱ���Ƚ����ͨ��2Ԥװ�����ã�ʹ��Ԥװ�� */
//  TIM_OC2PreloadConfig(DCMOTOR_BRUSH_TIMx, TIM_OCPreload_Enable);

//  /* ��ʱ�����ͨ��3ģʽ���� */
//  /* ����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM */
//  TIM_OCInitStructure.TIM_Pulse = 1800-1;
//  /* ��ʼ����ʱ��ͨ��3���PWM */
//  TIM_OC3Init(DCMOTOR_BRUSH_TIMx, &TIM_OCInitStructure);
//  /* ��ʱ���Ƚ����ͨ��3Ԥװ�����ã�ʹ��Ԥװ�� */
//  TIM_OC3PreloadConfig(DCMOTOR_BRUSH_TIMx, TIM_OCPreload_Enable);
  
  /* ʹ�ܶ�ʱ�����ؼĴ���ARR */
  TIM_ARRPreloadConfig(DCMOTOR_BRUSH_TIMx, ENABLE);

  /* ʹ�ܶ�ʱ�� */
  TIM_Cmd(DCMOTOR_BRUSH_TIMx, ENABLE);
  
  /* TIM�����ʹ�� */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

/**
  * ��������: TIMx ���PWM�źų�ʼ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ����ֻҪ�����������TIMx������ͨ���ͻ���PWM�ź����
  */
void DCMOTOR_BRUSH_TIMx_PWM_Init(void)
{
	DCMOTOR_BRUSH_TIMx_GPIO_Config();
	DCMOTOR_BRUSH_TIMx_Configuration();	
}

/**
  * ��������: ֱ���������
  * �������: number�������ţ�֧�������������
  *             ������1����Ӧ�߼���ʱ��ͨ��1�ͻ���ͨ��1
  *                   2����Ӧ�߼���ʱ��ͨ��2�ͻ���ͨ��2
  *                   3����Ӧ�߼���ʱ��ͨ��3�ͻ���ͨ��3
  *                   4��ʹ���������ת��
  *                   5�����������ͣ��
  *           direction������������
  *             ������0��Ŀ����ͣ��
  *                   1����ת
  *                   2����ת
  *           speed������ٶȵ���
  *             ������0 - 3600 ��ֵԽ���ٶ�Խ��
  * �� �� ֵ: ��
  * ˵    ����ֻҪ�����������TIMx������ͨ���ͻ���PWM�ź����
  */
void DCMOTOR_25GA370_Contrl(uint8_t number,uint8_t direction,uint16_t speed)
{
  switch (number)
  {
    case 1:
      if(direction==1)
      {
        TIM_CCxCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_1,TIM_CCx_Enable);
        TIM_CCxNCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_1,TIM_CCxN_Disable);
      }
      else if(direction==2)
      {
        TIM_CCxCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_1,TIM_CCx_Disable);
        TIM_CCxNCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_1,TIM_CCxN_Enable);
      }
      else
      {
        TIM_CCxCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_1,TIM_CCx_Disable);
        TIM_CCxNCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_1,TIM_CCxN_Disable);
      }
      TIM_SetCompare1(DCMOTOR_BRUSH_TIMx,speed);
      break; 
//    case 2:
//      if(direction==1)
//      {
//        TIM_CCxCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_2,TIM_CCx_Enable);
//        TIM_CCxNCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_2,TIM_CCxN_Disable);
//      }
//      else if(direction==2)
//      {
//        TIM_CCxCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_2,TIM_CCx_Disable);
//        TIM_CCxNCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_2,TIM_CCxN_Enable);
//      }
//      else
//      {
//        TIM_CCxCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_2,TIM_CCx_Disable);
//        TIM_CCxNCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_2,TIM_CCxN_Disable);
//      }
//      TIM_SetCompare2(DCMOTOR_BRUSH_TIMx,speed);
//    break; 
//   case 3:
//      if(direction==1)
//      {
//        TIM_CCxCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_2,TIM_CCx_Enable);
//        TIM_CCxNCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_2,TIM_CCxN_Disable);
//      }
//      else if(direction==2)
//      {
//        TIM_CCxCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_2,TIM_CCx_Disable);
//        TIM_CCxNCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_2,TIM_CCxN_Enable);
//      }
//      else
//      {
//        TIM_CCxCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_2,TIM_CCx_Disable);
//        TIM_CCxNCmd(DCMOTOR_BRUSH_TIMx,TIM_Channel_2,TIM_CCxN_Disable);
//      }
//      TIM_SetCompare3(DCMOTOR_BRUSH_TIMx,speed);
//    break;
   case 4:
     TIM_CtrlPWMOutputs(DCMOTOR_BRUSH_TIMx,ENABLE);  // ʹ�����PWM����ʼת��
     break;
   case 5:
     TIM_CtrlPWMOutputs(DCMOTOR_BRUSH_TIMx,DISABLE);  // ֹͣ���PWM��ͣ��
     break;
   default:
     TIM_CtrlPWMOutputs(DCMOTOR_BRUSH_TIMx,DISABLE);  // ֹͣ���PWM��ͣ��
     break;
  }      
}


