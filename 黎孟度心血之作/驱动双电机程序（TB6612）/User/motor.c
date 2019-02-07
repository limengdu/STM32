/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "motor.h"
#include "stm32f10x_exti.h"

/*******************************************************************************
* 函 数 名         : MOTOR_GPIO_Config
* 函数功能		   : 控制GPIO：PB12/PB13/PB14/PB15
                     电机MOTOR：TIM2_CH3/TIM2_CH4
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void MOTOR_GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	//定义一个GPIO_InitTypeDef类型的结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	//开启GPIOB的外设时钟
															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	
	//选择要控制的GPIOB引脚
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	//设置引脚模式为通用推挽输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	//设置引脚速率为50MHz
  	GPIO_Init(GPIOB, &GPIO_InitStructure);		  
	//调用库函数，初始化GPIOB

	GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	//低电平，确保初始状态下电机处于停止状态
	
	//GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14);
	//GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_15);
	//单电机控制
}

/*******************************************************************************
* 函 数 名         : TIM2_GPIO_Config
* 函数功能		   : 配置TIM2复用输出PWM时用到的I/O
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
static void TIM2_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	//PCLK1经过2倍频后作为TIM2的时钟源等于72MHz

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* 函 数 名         : TIM2_Mode_Config
* 函数功能		   : 配置TIM2输出的PWM信号的模式，如周期、极性、占空比
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
static void TIM2_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;

	/* PWM信号电平跳变值 */
	//u16 CCR1_Val = 500;        
	//u16 CCR2_Val = 800;
	u16 CCR3_Val = 0;
	u16 CCR4_Val = 0;
	 
	TIM_TimeBaseStructure.TIM_Period = 1000 ;       
	//ARR 当定时器从0计数到999，即为1000次，为一个定时周期
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	    
	//设置预分频：不预分频，即为72MHz psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	
	//设置时钟分频系数：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	//向上计数模式

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	   
	//设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
	//当定时器计数值小于CCR3_Val时为高电平

	TIM_OC3Init(TIM2, &TIM_OCInitStructure);//使能通道2
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	  
	//设置通道2的电平跳变值，输出另外一个占空比的PWM

	TIM_OC4Init(TIM2, &TIM_OCInitStructure);//使能通道3
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM2, ENABLE);		// 使能TIM3重载寄存器ARR

	TIM_Cmd(TIM2, ENABLE);                  //使能定时器2	
}

/*******************************************************************************
* 函 数 名         : TIM2_PWM_Init
* 函数功能		   : TIM2 输出PWM信号初始化，只要调用这个函数
 *                   TIM2的两个通道就会有PWM信号输出
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void TIM2_PWM_Init(void)
{
	TIM2_GPIO_Config(); //电机引脚和定时器通道IO配置
	TIM2_Mode_Config();	//配置TIM2输出的PWM信号的模式，如周期、极性、占空比
}



