/*-------------------------------------------------------------------------------
文件名称：tim.c
文件描述：定时器配置初始化功能函数。    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#include "tim.h"
#include "steering_engine.h"
#include "encoder.h"
#include "ultrasonic.h"

/*-------------------------------------------------------------------------------
函数名称：TIM2_Configuration
函数描述：舵机接口设置（TIM2） /PA1
输入参数：无
返回参数：无
备    注：无
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
	
  TIM_TimeBaseStructure.TIM_Period     		= Servo_Period - 1; 				// 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler  		= 144 - 1; 									// 设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 						// 设置时钟分频，这里采用不分频，即可以简单设置为0
	TIM_TimeBaseStructure.TIM_CounterMode	  = TIM_CounterMode_Up; 			// TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM1;							// 选择定时器模式，TIM脉冲宽度调制模式1 （在向上计数时，一旦TIMx_CNT<TIMx_CCR1时通道1为有效电平，否则为无效电平）aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2d0a2tuZC9hcnRpY2xlL2RldGFpbHMvMzkyOTYxNTE=
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;				// 比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_Low;						// 输出比较极性低 （即有效电平为低电平）
	TIM_OCInitStructure.TIM_Pulse 			= 0;														// 指定要加载到寄存器的脉冲值
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);														// 根据结构体信息进行初始化
	
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  									// 使能定时器TIM2在CCR2上的预装载值
	TIM_ARRPreloadConfig(TIM2, ENABLE);																	// 使能TIM2在ARR上的预装载寄存器
	TIM_Cmd(TIM2, ENABLE);																							// 使能定时器TIM2
}

/*-------------------------------------------------------------------------------
函数名称：TIM3_Configuration
函数描述：编码器接口设置（TIM3） /PA6-A相  PA7-B相
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void TIM3_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  						  // GPIOA外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);								// TIM3时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	                                                       				
	GPIO_InitStructure.GPIO_Pin 		= GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IPU;          					// 设置为上拉输入模式 
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;	   							// IO口的速率为50M 
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   										// IO口配置函数
	GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET); 

  TIM_TimeBaseStructure.TIM_Period 				= ENCODER_RESOLUTION - 1; 	// 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler 		= 0; 												// 设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     				// 设置时钟分频，这里采用不分频，即可以简单设置为0
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;  			// TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 										// TIM3初始化
	
	/* 设置定时器3为编码器模式  IT1 IT2为上升沿计数 */
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge); 	// 编码器计数模式设置为四倍频(A、B相双边沿)以提高精度
	TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter 				= 6;      									// 输入滤波器 					aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2d0a2tuZC9hcnRpY2xlL2RldGFpbHMvNTIxODczNzA=
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);      													// 清除所有标志位
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 													// 允许中断更新
  TIM_SetCounter(TIM3, 0);																						// TIM3->CNT = 0;	
	TIM_Cmd(TIM3, ENABLE);
}

/*-------------------------------------------------------------------------------
函数名称：TIM5_Configuration
函数描述：TIM5输入捕获初始化（超声波模块）
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void TIM5_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM5_ICInitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

/*
 *  （1）MCU主频 / 预分频值 = 定时器频率
 *	（2）1 / 定时器频率     = 定时器周期（1个）
 *  （3）定时器周期（1个） * 数量 = 定时器定时时间	
 */
  TIM_TimeBaseStructure.TIM_Period 						= TIM5_Period - 1;		  		// 设置自动重装载寄存器周期的值  1/(72MHz / 72) * 10000 = 10000us 
  TIM_TimeBaseStructure.TIM_Prescaler 				= 72 - 1;										// 设置TIM5预分频值    1Mhz的计数频率（1us计数）
  TIM_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;       			// 设置时钟分频，这里采用不分频，即可以简单设置为0
  TIM_TimeBaseStructure.TIM_CounterMode 			= TIM_CounterMode_Up; 			// TIM向上计数模式
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
/* 初始化TIM5输入捕获参数*/
	TIM5_ICInitStructure.TIM_Channel 						= TIM_Channel_1; 						// TIM5_CH1作为IC1输入端
	TIM5_ICInitStructure.TIM_ICPolarity 				= TIM_ICPolarity_Rising;		// 上升沿捕获
	TIM5_ICInitStructure.TIM_ICSelection 				= TIM_ICSelection_DirectTI; // 管脚与寄存器对应关系 IC1映射到TI5上
	TIM5_ICInitStructure.TIM_ICPrescaler 				= TIM_ICPSC_DIV1;						// 配置输入分频:不分频 
	TIM5_ICInitStructure.TIM_ICFilter 					= 0x00;											// 配置输入滤波器:不滤波 (根据自己情况，其可用于超声波模块滤波处理)
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);   																// 清除更新中断，以免一打开中断立即产生中断
  TIM_ITConfig(TIM5, TIM_IT_Update|TIM_IT_CC1, ENABLE);										// 允许更新中断和事件捕获中断
  TIM_Cmd(TIM5, ENABLE);																									// 使能TIM5
}

/*-------------------------------------------------------------------------------
函数名称：TIM6_Configuration
函数描述：周期循环事件定时初始化
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void TIM6_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

/*
 *  （1）MCU主频 / 预分频值 = 定时器频率
 *	（2）1 / 定时器频率     = 定时器周期（1个）
 *  （3）定时器周期（1个） * 数量 = 定时器定时时间	
 */
  TIM_TimeBaseStructure.TIM_Period 						= TIM6_Period - 1;		  // 设置自动重装载寄存器周期的值  1/(72MHz / 72) * 500 = 500us 
  TIM_TimeBaseStructure.TIM_Prescaler 				= 7200 - 1;								// 设置TIM7预分频值		
  TIM_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;       	// 设置时钟分频，这里采用不分频，即可以简单设置为0
  TIM_TimeBaseStructure.TIM_CounterMode 			= TIM_CounterMode_Up; 	// TIM向上计数模式
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
   
  TIM_UpdateRequestConfig(TIM6, TIM_UpdateSource_Regular);						// 设置 TIMx 更新请求源
  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);													// 允许更新中断
  TIM_Cmd(TIM6, ENABLE);																							// 使能TIM7
}

/*-------------------------------------------------------------------------------
函数名称：TIM7_Configuration
函数描述：周期循环事件定时初始化
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void TIM7_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

/*
 *  （1）MCU主频 / 预分频值 = 定时器频率
 *	（2）1 / 定时器频率     = 定时器周期（1个）
 *  （3）定时器周期（1个） * 数量 = 定时器定时时间	
 */
  TIM_TimeBaseStructure.TIM_Period 						= TIM7_Period - 1;		  // 设置自动重装载寄存器周期的值  1/(72MHz / 72) * 1000 = 1000us 
  TIM_TimeBaseStructure.TIM_Prescaler 				= 72 - 1;								// 设置TIM7预分频值		
  TIM_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;       	// 设置时钟分频，这里采用不分频，即可以简单设置为0
  TIM_TimeBaseStructure.TIM_CounterMode 			= TIM_CounterMode_Up; 	// TIM向上计数模式
  TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
   
  TIM_UpdateRequestConfig(TIM7, TIM_UpdateSource_Regular);						// 设置 TIMx 更新请求源
  TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);													// 允许更新中断
  TIM_Cmd(TIM7, ENABLE);																							// 使能TIM7
}

/*-------------------------------------------------------------------------------
函数名称：TIM8_Configuration
函数描述：TIM8四通道分别输出PWM1/PWM2,对应引脚为PC6/PC7
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void TIM8_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

	/* GPIO、外设时钟设定 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

	/*	GPIO参数设定 */
  GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_6 | GPIO_Pin_7;    
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       								// 20纳秒周期（GPIO）
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;       
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
	 
	/* 定时器参数设定 */
	TIM_TimeBaseStructure.TIM_Prescaler 				= 0;												// 设置预分频值
	TIM_TimeBaseStructure.TIM_CounterMode 			= TIM_CounterMode_Up;				// 向上计数模式
	TIM_TimeBaseStructure.TIM_Period 						= PWMPeriod - 1;						// 设置自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;							// 设置时钟分割(若没有特殊情况，默认为TIM_CKD_DIV1。TIM_ClockDivision的作用就是在未分频之前 根据要求建立新的分频器，确定定时器，确定一定的延时时间，在此时间内完成一定预期的功能)  aHR0cDovL2Jsb2cuc2luYS5jb20uY24vcy9ibG9nXzc2YzU0NTM5MDEwMG92ZmouaHRtbA==
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;												// 仅高级定时器有该项(用于重复计数，该项是重复溢出0次才给一个溢出中断) 
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);													// 根据指定的参数初始化TIM8					
	
	/* 定时器PWM模式参数设定 */
	TIM_OCInitStructure.TIM_OCMode 				= TIM_OCMode_PWM2;								// TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState 	= TIM_OutputState_Enable;					// 使能指定TIM输出比较状态
	TIM_OCInitStructure.TIM_OutputNState  = TIM_OutputNState_Disable;				// 禁用指定TIM互补输出比较状态
	TIM_OCInitStructure.TIM_OCPolarity 		= TIM_OCPolarity_Low;							// TIM输出极性低
	TIM_OCInitStructure.TIM_OCNPolarity 	= TIM_OCNPolarity_High;						// TIM8输出比较N极性高

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);												
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	
	TIM_SetCompare1(TIM8, 0);                                               // TIM8->CCR1 = 0;  TIM8的CCR1位初始化为0
	TIM_SetCompare2(TIM8, 0);																								// TIM8->CCR2 = 0; 	TIM8的CCR2位初始化为0
 
	TIM_Cmd(TIM8, ENABLE);															// 使能定时器TIM8
	TIM_CtrlPWMOutputs(TIM8, ENABLE);										// PWM输出使能
}

/*-------------------------------------------------------------------------------
函数名称：TIM_Init
函数描述：针对指定TIM定时器进行使用前的初始化
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void TIM_Init(void)
{
	TIM2_Configuration();																										// TIM2配置初始化
	TIM3_Configuration();																										// TIM3配置初始化
	TIM5_Configuration();																										// TIM5配置初始化
	TIM6_Configuration();																										// TIM6配置初始化
	TIM7_Configuration();																										// TIM7配置初始化
	TIM8_Configuration();																										// TIM8配置初始化
}
