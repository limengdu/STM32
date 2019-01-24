/* Includes ------------------------------------------------------------------*/
#include "encoder.h" 

/*******************************************************************************
* 函 数 名         : ENCODER_TIMx_GPIO_Config
* 函数功能		   : 初始化定时器TIM3引脚
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
static void ENCODER_TIMx_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  ENCODER_TIM_GPIO_APBxClock_FUN(ENCODER_TIM_GPIO_CLK, ENABLE); 
  //使能定时器TIM3通道3引脚GPIOB的时钟

  GPIO_InitStructure.GPIO_Pin =  ENCODER_TIM_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ENCODER_TIM_PORT, &GPIO_InitStructure);  
  //配置定时器通道3引脚模式——PB0
}

/*******************************************************************************
* 函 数 名         : TIMx_NVIC_Configuration
* 函数功能		   : 配置嵌套向量中断控制器NVIC
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
static void TIMx_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  //选择中断优先级配置组为2个抢占式优先级和2个子优先级

  NVIC_InitStructure.NVIC_IRQChannel = ENCODER_TIMx_IRQn;  
  //配置TIM3_IRQ中断为中断源
	
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  //设置抢占式优先级为0
	
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  //设置子优先级为2
	
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  //使能外部中断通道
	
  NVIC_Init(&NVIC_InitStructure);
}

/*
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT 重新计数
 *                    TIMx_CCR(电平发生变化)
 * 信号周期=(TIMx_ARR +1 ) * 时钟周期
 * 占空比=TIMx_CCR/(TIMx_ARR +1)
 *    _______    ______     _____      ____       ___        __         _
 * |_|       |__|      |___|     |____|    |_____|   |______|  |_______| |_________|
 *
 */
/*******************************************************************************
* 函 数 名         : ENCODER_TIMx_Configuration
* 函数功能		   : 配置输出PWM、输入捕获的TIM3
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
static void ENCODER_TIMx_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef        TIM_ICInitStructure;

  //初始化TIM3配置
  ENCODER_TIM_APBxClock_FUN(ENCODER_TIM_CLK,ENABLE);
  //使能定时器TIM3时钟

  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_Period;
  //定时周期: 65535+1
	
  TIM_TimeBaseStructure.TIM_Prescaler = ENCODER_TIM_Prescaler;
  //设置预分频：(72-1),输出脉冲频率：72MHz/(65535+1)/(72-1+1)
	
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
  //设置时钟分频系数：不分频(这里用不到)
	
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  //向上计数模式
	
  TIM_TimeBaseInit(ENCODER_TIMx, &TIM_TimeBaseStructure);

  //初始化TIM3输入捕获
  TIM_ICInitStructure.TIM_Channel     = ENCODER_TIM_Channel_x;
/*设置输入捕获滤波器——TIM_Channel_3
输入捕获滤波器ICF[3:0]，这个用于设置采样频率和数字滤波器长度。
其中：fCK_INT是定时器的输入频率，fDTS是根据TIMx_CR1的CKD[1:0]的设置来确定的。
数字滤波器由一个事件计数器组成，它记录到N个事件后会产生一个输出的跳变。
也就是说连续N次采样，如果都是高电平，则说明这是一个有效的触发，就会进入输入捕捉中断
（如果设置了的话）。
这样就可以滤除那些高电平脉宽低于8个采样周期的脉冲信号，从而达到滤波的作用。
*/

  TIM_ICInitStructure.TIM_ICPolarity  = ENCODER_TIM_ICPolarity;
  //设置输入捕捉极性——上升沿捕获

  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  //映射到TI1上

  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  //设置输入捕获分频器——不分频（这里设置的是每N个事件触发一次捕捉）

  TIM_ICInitStructure.TIM_ICFilter    = 0x00;
  //IC1F=0000 配置输入滤波器 不滤波
  
  TIM_ICInit(ENCODER_TIMx, &TIM_ICInitStructure);  
  
  TIMx_NVIC_Configuration();
  //配置NVIC
  
  TIM_ITConfig(ENCODER_TIMx,ENCODER_TIM_IT_CCx, ENABLE);
  //允许更新中断 ,允许CC1IE捕获中断
	
  TIM_Cmd(ENCODER_TIMx, ENABLE);
  //使能定时器  
}

/*******************************************************************************
* 函 数 名         : TIMx_DCmotor_ENCODER_Init
* 函数功能		   : TIM3通道3输入捕获初始化
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void TIMx_DCmotor_ENCODER_Init(void)
{
	ENCODER_TIMx_GPIO_Config();    //定时器TIM3引脚配置
	ENCODER_TIMx_Configuration();  //定时器TIM3输入捕获配置
}

