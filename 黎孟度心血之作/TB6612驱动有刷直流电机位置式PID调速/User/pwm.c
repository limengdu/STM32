/* Includes ------------------------------------------------------------------*/
#include "pwm.h" 

/*******************************************************************************
* 函 数 名         : PWM_GPIO_Config
* 函数功能		   : 配置TIMx复用输出PWM时用到的I/O：PA8和PA11
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void PWM_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//使能定时器时钟
	MOTOR_TIM_APBxClock(MOTOR_TIM_CLK, ENABLE);

	//使能定时器通道引脚GPIO时钟
	MOTOR_TIM_GPIO_APBxClock(MOTOR_TIM_GPIO_CLK|RCC_APB2Periph_AFIO, ENABLE); 

    //配置定时器通道1输出引脚模式：复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin =  MOTOR_TIM_CH1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_TIM_CH1_PORT, &GPIO_InitStructure);
	
	//配置定时器通道4输出引脚模式：复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin =  MOTOR_TIM_CH4_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_TIM_CH4_PORT, &GPIO_InitStructure);
}


/*******************************************************************************
* 函 数 名         : PWM_TIMx_Config
* 函数功能		   : 配置TIMx输出的PWM信号的模式，如周期、极性、占空比
* 输    入         : 无
* 输    出         : 无
* 说    明         ：
         TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT 重新计数
                           TIMx_CCR(电平发生变化)
                    信号周期=(TIMx_ARR +1 ) * 时钟周期
                       占空比=TIMx_CCR/(TIMx_ARR +1)
*                             黎孟度心血之作                                   *
*******************************************************************************/
void PWM_TIMx_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;

	//定时器基本参数设定	
	//当定时器从0计数到3600-1，即为3600次，为一个定时周期
	TIM_TimeBaseStructure.TIM_Period = 3600-1;
	
	//设置预分频：不预分频，即为72MHz,输出脉冲频率：72MHz/3600=20KHz
	//同一个定时器的不同通道PWM的频率只能是相同的，不同通道可以设置为不同的占空比
	TIM_TimeBaseStructure.TIM_Prescaler = 1;
	
	//设置时钟分频系数：不分频(这里用不到)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	//向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	//重复计算器
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(MOTOR_TIMx, &TIM_TimeBaseStructure);

	//定时器输出通道1模式配置
	//模式配置：PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	
	//输出状态设置：使能输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	
	//设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_Pulse = 1800-1;
	
	//当定时器计数值小于CCR1_Val时为低电平
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	//只有TIM1和TIM8才有互补+死区输出!
	//指定空闲状态下的TIM输出比较的引脚状态：低
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
	//初始化定时器通道1输出PWM
	TIM_OC1Init(MOTOR_TIMx, &TIM_OCInitStructure);
	
	//初始化定时器通道4输出PWM
	TIM_OC4Init(MOTOR_TIMx, &TIM_OCInitStructure);
  
    //有关OC/OCN使能的细节，参见13.4.9 TIM1和TIM8捕获/比较使能寄存器(TIMx_CCER)。
	TIM_OC1PreloadConfig(MOTOR_TIMx, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(MOTOR_TIMx, TIM_OCPreload_Enable);
  
	//使能定时器重载寄存器ARR
	TIM_ARRPreloadConfig(MOTOR_TIMx, ENABLE);

	//使能定时器
	TIM_Cmd(MOTOR_TIMx, ENABLE);

	//TIM主输出使能(仅限于高级定时器)
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}


/*******************************************************************************
* 函 数 名         : TIMx_PWM_Init
* 函数功能		   : TIMx输出PWM信号初始化
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void TIMx_PWM_Init(void)
{
	PWM_GPIO_Config();   //配置TIMx复用输出PWM时用到的I/O
	PWM_TIMx_Config();   //配置TIMx输出的PWM信号的模式，如周期、极性、占空比
}
