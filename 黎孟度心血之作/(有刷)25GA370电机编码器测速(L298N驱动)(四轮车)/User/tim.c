/* Includes ------------------------------------------------------------------*/
#include "tim.h" 

/*******************************************************************************
* �� �� ��         : DCMOTOR_BRUSH_TIMx_GPIO_Config
* ��������		   : ����TIMx�������PWMʱ�õ���I/O
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
static void DCMOTOR_BRUSH_TIMx_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(DCMOTOR_BRUSH_TIM_CLK, ENABLE);
  //ʹ�ܶ�ʱ��ʱ��

  RCC_APB2PeriphClockCmd(DCMOTOR_BRUSH_TIM_GPIO_CLK|RCC_APB2Periph_AFIO, ENABLE); 
  //ʹ�ܶ�ʱ��ͨ������GPIOʱ��

  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DCMOTOR_BRUSH_TIM_CH1_PORT, &GPIO_InitStructure);
  //���ö�ʱ��ͨ��1�������ģʽ�������������ģʽ

//GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH2_PIN;
//GPIO_Init(DCMOTOR_BRUSH_TIM_CH2_PORT, &GPIO_InitStructure);
////���ö�ʱ��ͨ��2�������ģʽ

//GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH3_PIN;
//GPIO_Init(DCMOTOR_BRUSH_TIM_CH3_PORT, &GPIO_InitStructure);
////���ö�ʱ��ͨ��3�������ģʽ

  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH1N_PIN;
  GPIO_Init(DCMOTOR_BRUSH_TIM_CH1N_PORT, &GPIO_InitStructure);  
  //���ö�ʱ������ͨ��1�������ģʽ

//GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH2N_PIN;
//GPIO_Init(DCMOTOR_BRUSH_TIM_CH2N_PORT, &GPIO_InitStructure);  
////���ö�ʱ������ͨ��2�������ģʽ

//GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH3N_PIN;
//GPIO_Init(DCMOTOR_BRUSH_TIM_CH3N_PORT, &GPIO_InitStructure);   
////���ö�ʱ������ͨ��3�������ģʽ
}

/*
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT ���¼���
 *                    TIMx_CCR(��ƽ�����仯)
 * �ź�����=(TIMx_ARR +1 ) * ʱ������
 * ռ�ձ�=TIMx_CCR/(TIMx_ARR +1)
 */
/*******************************************************************************
* �� �� ��         : DCMOTOR_BRUSH_TIMx_Configuration
* ��������		   : ����TIMx�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
static void DCMOTOR_BRUSH_TIMx_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef        TIM_OCInitStructure;

  //��ʱ��������������
  TIM_TimeBaseStructure.TIM_Period = 3600-1;   	
  //����ʱ����0������3600-1����Ϊ3600�Σ�Ϊһ����ʱ����
	
  TIM_TimeBaseStructure.TIM_Prescaler = 1;
  //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz,�������Ƶ�ʣ�72MHz/3600=20KHz
  //ͬһ����ʱ���Ĳ�ͬͨ��PWM��Ƶ��ֻ������ͬ�ģ���ͬͨ����������Ϊ��ͬ��ռ�ձ�
	
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
  //����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
	
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  //���ϼ���ģʽ
	
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  //�ظ�������
	
  TIM_TimeBaseInit(DCMOTOR_BRUSH_TIMx, &TIM_TimeBaseStructure);

  //��ʱ�����ͨ��1ģʽ����
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  //ģʽ���ã�PWMģʽ2
  
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  //���״̬���ã�ʹ�����
  
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  //����ͨ�����״̬���ã�ʹ�����
  
  TIM_OCInitStructure.TIM_Pulse = 1800-1;
  //��������ֵ�������������������ֵʱ����ƽ��������
  
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  //����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ
  
  TIM_OC1Init(DCMOTOR_BRUSH_TIMx, &TIM_OCInitStructure);
  //��ʼ����ʱ��ͨ��1���PWM
  
  TIM_OC1PreloadConfig(DCMOTOR_BRUSH_TIMx, TIM_OCPreload_Enable);
  //��ʱ���Ƚ����ͨ��1Ԥװ�����ã�ʹ��Ԥװ��
  
//��ʱ�����ͨ��2ģʽ����
//TIM_OCInitStructure.TIM_Pulse = 1800-1;
//����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM

//TIM_OC2Init(DCMOTOR_BRUSH_TIMx, &TIM_OCInitStructure);
//��ʼ����ʱ��ͨ��2���PWM

//TIM_OC2PreloadConfig(DCMOTOR_BRUSH_TIMx, TIM_OCPreload_Enable);
//��ʱ���Ƚ����ͨ��2Ԥװ�����ã�ʹ��Ԥװ��

//��ʱ�����ͨ��3ģʽ����
//TIM_OCInitStructure.TIM_Pulse = 1800-1;
//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM

//TIM_OC3Init(DCMOTOR_BRUSH_TIMx, &TIM_OCInitStructure);
//��ʼ����ʱ��ͨ��3���PWM

//TIM_OC3PreloadConfig(DCMOTOR_BRUSH_TIMx, TIM_OCPreload_Enable);
//��ʱ���Ƚ����ͨ��3Ԥװ�����ã�ʹ��Ԥװ��

  TIM_ARRPreloadConfig(DCMOTOR_BRUSH_TIMx, ENABLE);  
  //ʹ�ܶ�ʱ�����ؼĴ���ARR

  TIM_Cmd(DCMOTOR_BRUSH_TIMx, ENABLE);
  //ʹ�ܶ�ʱ��

  TIM_CtrlPWMOutputs(TIM1, ENABLE);  
  //TIM�����ʹ��
}

/*******************************************************************************
* �� �� ��         : DCMOTOR_BRUSH_TIMx_PWM_Init
* ��������		   : TIMx ���PWM�źų�ʼ��
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void DCMOTOR_BRUSH_TIMx_PWM_Init(void)
{
	DCMOTOR_BRUSH_TIMx_GPIO_Config();   //����TIMx�������PWMʱ�õ���I/O
	DCMOTOR_BRUSH_TIMx_Configuration();	//����TIMx�����PWM�źŵ�ģʽ
}

/*******************************************************************************
* �� �� ��         : DCMOTOR_25GA370_Contrl
* ��������		   : ֱ���������
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         ������number�������ţ�֧�������������(ֻ����ͨ��1)
*                    ֵ        ��1������Ӧ�߼���ʱ��ͨ��1�ͻ���ͨ��1
*                                2������Ӧ�߼���ʱ��ͨ��2�ͻ���ͨ��2
*                                3������Ӧ�߼���ʱ��ͨ��3�ͻ���ͨ��3
*                                4����ʹ���������ת��
*                                5�������������ͣ��
*
*                    ����direction������������
*                    ֵ        ��0����Ŀ����ͣ��
*                                1������ת
*                                2������ת
*
*                    ����speed������ٶȵ���
*                    ֵ        ��0 - 3600����ֵԽ���ٶ�Խ��
*
*                    ֻҪ�����������TIMx������ͨ���ͻ���PWM�ź����
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
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
     TIM_CtrlPWMOutputs(DCMOTOR_BRUSH_TIMx,ENABLE);   // ʹ�����PWM����ʼת��
     break;
   case 5:
     TIM_CtrlPWMOutputs(DCMOTOR_BRUSH_TIMx,DISABLE);  // ֹͣ���PWM��ͣ��
     break;
   default:
     TIM_CtrlPWMOutputs(DCMOTOR_BRUSH_TIMx,DISABLE);  // ֹͣ���PWM��ͣ��
     break;
  }      
}


