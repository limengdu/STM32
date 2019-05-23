/*-------------------------------------------------------------------------------
�ļ����ƣ�tim.c
�ļ���������ʱ�����ó�ʼ�����ܺ�����    
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "tim.h"
#include "steering_engine.h"
#include "encoder.h"
#include "ultrasonic.h"

/*-------------------------------------------------------------------------------
�������ƣ�TIM2_Configuration
��������������ӿ����ã�TIM2�� /PA1
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void TIM2_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
	                                                      				
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_1;			   								// PA1 TIM2_CH2
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF_PP;          					
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;	   
	GPIO_Init(GPIOA, &GPIO_InitStructure);				  
	
  TIM_TimeBaseStructure.TIM_Period     		= Servo_Period - 1; 				// ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler  		= 144 - 1; 									// ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 						// ����ʱ�ӷ�Ƶ��������ò���Ƶ�������Լ�����Ϊ0
	TIM_TimeBaseStructure.TIM_CounterMode	  = TIM_CounterMode_Up; 			// TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM1;							// ѡ��ʱ��ģʽ��TIM�����ȵ���ģʽ1 �������ϼ���ʱ��һ��TIMx_CNT<TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2d0a2tuZC9hcnRpY2xlL2RldGFpbHMvMzkyOTYxNTE=
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;				// �Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_Low;						// ����Ƚϼ��Ե� ������Ч��ƽΪ�͵�ƽ��
	TIM_OCInitStructure.TIM_Pulse 			= 0;														// ָ��Ҫ���ص��Ĵ���������ֵ
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);														// ���ݽṹ����Ϣ���г�ʼ��
	
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  									// ʹ�ܶ�ʱ��TIM2��CCR2�ϵ�Ԥװ��ֵ
	TIM_ARRPreloadConfig(TIM2, ENABLE);																	// ʹ��TIM2��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM2, ENABLE);																							// ʹ�ܶ�ʱ��TIM2
}

/*-------------------------------------------------------------------------------
�������ƣ�TIM3_Configuration
�����������������ӿ����ã�TIM3�� /PA6-A��  PA7-B��
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void TIM3_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  						  // GPIOA����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);								// TIM3ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	                                                       				
	GPIO_InitStructure.GPIO_Pin 		= GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IPU;          					// ����Ϊ��������ģʽ 
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;	   							// IO�ڵ�����Ϊ50M 
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   										// IO�����ú���
	GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET); 

  TIM_TimeBaseStructure.TIM_Period 				= ENCODER_RESOLUTION - 1; 	// ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler 		= 0; 												// ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     				// ����ʱ�ӷ�Ƶ��������ò���Ƶ�������Լ�����Ϊ0
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;  			// TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 										// TIM3��ʼ��
	
	/* ���ö�ʱ��3Ϊ������ģʽ  IT1 IT2Ϊ�����ؼ��� */
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge); 	// ����������ģʽ����Ϊ�ı�Ƶ(A��B��˫����)����߾���
	TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter 				= 6;      									// �����˲��� 					aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2d0a2tuZC9hcnRpY2xlL2RldGFpbHMvNTIxODczNzA=
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);      													// ������б�־λ
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 													// �����жϸ���
  TIM_SetCounter(TIM3, 0);																						// TIM3->CNT = 0;	
	TIM_Cmd(TIM3, ENABLE);
}

/*-------------------------------------------------------------------------------
�������ƣ�TIM5_Configuration
����������TIM5���벶���ʼ����������ģ�飩
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void TIM5_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM5_ICInitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

/*
 *  ��1��MCU��Ƶ / Ԥ��Ƶֵ = ��ʱ��Ƶ��
 *	��2��1 / ��ʱ��Ƶ��     = ��ʱ�����ڣ�1����
 *  ��3����ʱ�����ڣ�1���� * ���� = ��ʱ����ʱʱ��	
 */
  TIM_TimeBaseStructure.TIM_Period 						= TIM5_Period - 1;		  		// �����Զ���װ�ؼĴ������ڵ�ֵ  1/(72MHz / 72) * 10000 = 10000us 
  TIM_TimeBaseStructure.TIM_Prescaler 				= 72 - 1;										// ����TIM5Ԥ��Ƶֵ    1Mhz�ļ���Ƶ�ʣ�1us������
  TIM_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;       			// ����ʱ�ӷ�Ƶ��������ò���Ƶ�������Լ�����Ϊ0
  TIM_TimeBaseStructure.TIM_CounterMode 			= TIM_CounterMode_Up; 			// TIM���ϼ���ģʽ
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
/* ��ʼ��TIM5���벶�����*/
	TIM5_ICInitStructure.TIM_Channel 						= TIM_Channel_1; 						// TIM5_CH1��ΪIC1�����
	TIM5_ICInitStructure.TIM_ICPolarity 				= TIM_ICPolarity_Rising;		// �����ز���
	TIM5_ICInitStructure.TIM_ICSelection 				= TIM_ICSelection_DirectTI; // �ܽ���Ĵ�����Ӧ��ϵ IC1ӳ�䵽TI5��
	TIM5_ICInitStructure.TIM_ICPrescaler 				= TIM_ICPSC_DIV1;						// ���������Ƶ:����Ƶ 
	TIM5_ICInitStructure.TIM_ICFilter 					= 0x00;											// ���������˲���:���˲� (�����Լ������������ڳ�����ģ���˲�����)
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);   																// ��������жϣ�����һ���ж����������ж�
  TIM_ITConfig(TIM5, TIM_IT_Update|TIM_IT_CC1, ENABLE);										// ��������жϺ��¼������ж�
  TIM_Cmd(TIM5, ENABLE);																									// ʹ��TIM5
}

/*-------------------------------------------------------------------------------
�������ƣ�TIM6_Configuration
��������������ѭ���¼���ʱ��ʼ��
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void TIM6_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

/*
 *  ��1��MCU��Ƶ / Ԥ��Ƶֵ = ��ʱ��Ƶ��
 *	��2��1 / ��ʱ��Ƶ��     = ��ʱ�����ڣ�1����
 *  ��3����ʱ�����ڣ�1���� * ���� = ��ʱ����ʱʱ��	
 */
  TIM_TimeBaseStructure.TIM_Period 						= TIM6_Period - 1;		  // �����Զ���װ�ؼĴ������ڵ�ֵ  1/(72MHz / 72) * 500 = 500us 
  TIM_TimeBaseStructure.TIM_Prescaler 				= 7200 - 1;								// ����TIM7Ԥ��Ƶֵ		
  TIM_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;       	// ����ʱ�ӷ�Ƶ��������ò���Ƶ�������Լ�����Ϊ0
  TIM_TimeBaseStructure.TIM_CounterMode 			= TIM_CounterMode_Up; 	// TIM���ϼ���ģʽ
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
   
  TIM_UpdateRequestConfig(TIM6, TIM_UpdateSource_Regular);						// ���� TIMx ��������Դ
  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);													// ��������ж�
  TIM_Cmd(TIM6, ENABLE);																							// ʹ��TIM7
}

/*-------------------------------------------------------------------------------
�������ƣ�TIM7_Configuration
��������������ѭ���¼���ʱ��ʼ��
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void TIM7_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

/*
 *  ��1��MCU��Ƶ / Ԥ��Ƶֵ = ��ʱ��Ƶ��
 *	��2��1 / ��ʱ��Ƶ��     = ��ʱ�����ڣ�1����
 *  ��3����ʱ�����ڣ�1���� * ���� = ��ʱ����ʱʱ��	
 */
  TIM_TimeBaseStructure.TIM_Period 						= TIM7_Period - 1;		  // �����Զ���װ�ؼĴ������ڵ�ֵ  1/(72MHz / 72) * 1000 = 1000us 
  TIM_TimeBaseStructure.TIM_Prescaler 				= 72 - 1;								// ����TIM7Ԥ��Ƶֵ		
  TIM_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;       	// ����ʱ�ӷ�Ƶ��������ò���Ƶ�������Լ�����Ϊ0
  TIM_TimeBaseStructure.TIM_CounterMode 			= TIM_CounterMode_Up; 	// TIM���ϼ���ģʽ
  TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
   
  TIM_UpdateRequestConfig(TIM7, TIM_UpdateSource_Regular);						// ���� TIMx ��������Դ
  TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);													// ��������ж�
  TIM_Cmd(TIM7, ENABLE);																							// ʹ��TIM7
}

/*-------------------------------------------------------------------------------
�������ƣ�TIM8_Configuration
����������TIM8��ͨ���ֱ����PWM1/PWM2,��Ӧ����ΪPC6/PC7
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void TIM8_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

	/* GPIO������ʱ���趨 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

	/*	GPIO�����趨 */
  GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_6 | GPIO_Pin_7;    
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       								// 20�������ڣ�GPIO��
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;       
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
	 
	/* ��ʱ�������趨 */
	TIM_TimeBaseStructure.TIM_Prescaler 				= 0;												// ����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_CounterMode 			= TIM_CounterMode_Up;				// ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period 						= PWMPeriod - 1;						// �����Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;							// ����ʱ�ӷָ�(��û�����������Ĭ��ΪTIM_CKD_DIV1��TIM_ClockDivision�����þ�����δ��Ƶ֮ǰ ����Ҫ�����µķ�Ƶ����ȷ����ʱ����ȷ��һ������ʱʱ�䣬�ڴ�ʱ�������һ��Ԥ�ڵĹ���)  aHR0cDovL2Jsb2cuc2luYS5jb20uY24vcy9ibG9nXzc2YzU0NTM5MDEwMG92ZmouaHRtbA==
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;												// ���߼���ʱ���и���(�����ظ��������������ظ����0�βŸ�һ������ж�) 
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);													// ����ָ���Ĳ�����ʼ��TIM8					
	
	/* ��ʱ��PWMģʽ�����趨 */
	TIM_OCInitStructure.TIM_OCMode 				= TIM_OCMode_PWM2;								// TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState 	= TIM_OutputState_Enable;					// ʹ��ָ��TIM����Ƚ�״̬
	TIM_OCInitStructure.TIM_OutputNState  = TIM_OutputNState_Disable;				// ����ָ��TIM��������Ƚ�״̬
	TIM_OCInitStructure.TIM_OCPolarity 		= TIM_OCPolarity_Low;							// TIM������Ե�
	TIM_OCInitStructure.TIM_OCNPolarity 	= TIM_OCNPolarity_High;						// TIM8����Ƚ�N���Ը�

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);												
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	
	TIM_SetCompare1(TIM8, 0);                                               // TIM8->CCR1 = 0;  TIM8��CCR1λ��ʼ��Ϊ0
	TIM_SetCompare2(TIM8, 0);																								// TIM8->CCR2 = 0; 	TIM8��CCR2λ��ʼ��Ϊ0
 
	TIM_Cmd(TIM8, ENABLE);															// ʹ�ܶ�ʱ��TIM8
	TIM_CtrlPWMOutputs(TIM8, ENABLE);										// PWM���ʹ��
}

/*-------------------------------------------------------------------------------
�������ƣ�TIM_Init
�������������ָ��TIM��ʱ������ʹ��ǰ�ĳ�ʼ��
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void TIM_Init(void)
{
	TIM2_Configuration();																										// TIM2���ó�ʼ��
	TIM3_Configuration();																										// TIM3���ó�ʼ��
	TIM5_Configuration();																										// TIM5���ó�ʼ��
	TIM6_Configuration();																										// TIM6���ó�ʼ��
	TIM7_Configuration();																										// TIM7���ó�ʼ��
	TIM8_Configuration();																										// TIM8���ó�ʼ��
}
