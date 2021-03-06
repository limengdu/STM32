/* Includes ------------------------------------------------------------------*/
#include "encoder.h"

/*******************************************************************************
* 函 数 名         : Encoder_Init_TIM2
* 函数功能		   : 把TIM2初始化为编码器接口模式
* 输    入         : 无
* 输    出         : 无
* 说    明         ：此处将定时器TIM2配置为编码器接口模式，
                     其中PA0对应编码器A相，PA1对应编码器B相
*                             黎孟度心血之作                                   *
*******************************************************************************/
void Encoder_Init_TIM2(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef       TIM_ICInitStructure;  
	GPIO_InitTypeDef        GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  //使能定时器TIM2的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;  //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);				  //初始化

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;            //预分频器 
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;//设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	//使用编码器模式3
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, 
	                           TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);                 //清除TIM的更新标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	TIM_SetCounter(TIM2,0);
	TIM_Cmd(TIM2, ENABLE); 
}


/*******************************************************************************
* 函 数 名         : Encoder_Init_TIM4
* 函数功能		   : 把TIM4初始化为编码器接口模式
* 输    入         : 无
* 输    出         : 无
* 说    明         ：此处将定时器TIM4配置为编码器接口模式，
                     其中PB6对应编码器A相，PB7对应编码器B相
*                             黎孟度心血之作                                   *
*******************************************************************************/
void Encoder_Init_TIM4(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef       TIM_ICInitStructure;  
	GPIO_InitTypeDef        GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  //使能定时器TIM4的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;  //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);				  //根据设定参数初始化PB

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;            //预分频器 
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;//设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	//使用编码器模式3
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
	                           TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);                 //清除TIM的更新标志位
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	TIM_SetCounter(TIM4,0);
	TIM_Cmd(TIM4, ENABLE); 
}


/*******************************************************************************
* 函 数 名         : Read_Encoder
* 函数功能		   : 单位时间读取编码器计数
* 输    入         : 定时器
* 输    出         : 速度值
*                             黎孟度心血之作                                   *
*******************************************************************************/
int Read_Encoder(u8 TIMX)
{
	int Encoder_TIM;    
	switch(TIMX)
	 {
	     case 2:  Encoder_TIM= (short)TIM2 -> CNT;break;
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;break;	
		 default: Encoder_TIM=0;
	 }
	return Encoder_TIM;
}
