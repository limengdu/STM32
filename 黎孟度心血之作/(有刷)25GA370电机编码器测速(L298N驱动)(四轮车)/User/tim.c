/**
  ******************************************************************************
  * 文件名程: bsp_DCmotor_brush_TIM.c 
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2015-10-04
  * 功    能: 直流有刷电机驱动实现
  ******************************************************************************
  * 说明：
  * 本例程配套硬石stm32开发板YS-F1Pro使用。
  * 
  * 淘宝：
  * 论坛：http://www.ing10bbs.com
  * 版权归硬石嵌入式开发团队所有，请勿商用。
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "tim.h" 

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/
/**
  * 函数功能: 配置TIMx复用输出PWM时用到的I/O
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
static void DCMOTOR_BRUSH_TIMx_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* 使能定时器始终 */
	DCMOTOR_BRUSH_TIM_APBxClock_FUN(DCMOTOR_BRUSH_TIM_CLK, ENABLE);

  /* 使能定时器通道引脚GPIO时钟 */
  DCMOTOR_BRUSH_TIM_GPIO_APBxClock_FUN(DCMOTOR_BRUSH_TIM_GPIO_CLK|RCC_APB2Periph_AFIO, ENABLE); 

  /* 配置定时器通道1输出引脚模式：复用推挽输出模式 */
  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DCMOTOR_BRUSH_TIM_CH1_PORT, &GPIO_InitStructure);

//  /* 配置定时器通道2输出引脚模式 */
//  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH2_PIN;
//  GPIO_Init(DCMOTOR_BRUSH_TIM_CH2_PORT, &GPIO_InitStructure);

//  /* 配置定时器通道3输出引脚模式 */
//  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH3_PIN;
//  GPIO_Init(DCMOTOR_BRUSH_TIM_CH3_PORT, &GPIO_InitStructure);
  
  /* 配置定时器互补通道1输出引脚模式 */
  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH1N_PIN;
  GPIO_Init(DCMOTOR_BRUSH_TIM_CH1N_PORT, &GPIO_InitStructure);
  
//  /* 配置定时器互补通道2输出引脚模式 */
//  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH2N_PIN;
//  GPIO_Init(DCMOTOR_BRUSH_TIM_CH2N_PORT, &GPIO_InitStructure);
//  
//  /* 配置定时器互补通道3输出引脚模式 */
//  GPIO_InitStructure.GPIO_Pin =  DCMOTOR_BRUSH_TIM_CH3N_PIN;
//  GPIO_Init(DCMOTOR_BRUSH_TIM_CH3N_PORT, &GPIO_InitStructure);  
}

/**
  * 函数功能: 配置TIMx输出的PWM信号的模式，如周期、极性、占空比
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
/*
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT 重新计数
 *                    TIMx_CCR(电平发生变化)
 * 信号周期=(TIMx_ARR +1 ) * 时钟周期
 * 占空比=TIMx_CCR/(TIMx_ARR +1)
 */
static void DCMOTOR_BRUSH_TIMx_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* 定时器基本参数始终 */		
  /* 当定时器从0计数到3600-1，即为3600次，为一个定时周期 */
  TIM_TimeBaseStructure.TIM_Period = 3600-1;   
  /* 设置预分频：不预分频，即为72MHz,输出脉冲频率：72MHz/3600=20KHz */
  /* 同一个定时器的不同通道PWM的频率只能是相同的，不同通道可以设置为不同的占空比 */
  TIM_TimeBaseStructure.TIM_Prescaler = 1;
  /* 设置时钟分频系数：不分频(这里用不到) */
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
  /* 向上计数模式 */
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  /* 重复计算器 */
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(DCMOTOR_BRUSH_TIMx, &TIM_TimeBaseStructure);

  /* 定时器输出通道1模式配置 */
  /* 模式配置：PWM模式1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  /* 输出状态设置：使能输出 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  /* 互补通道输出状态设置：使能输出 */
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  /* 设置跳变值，当计数器计数到这个值时，电平发生跳变 */
  TIM_OCInitStructure.TIM_Pulse = 1800-1;
  /* 当定时器计数值小于CCR1_Val时为低电平 */
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  /* 初始化定时器通道1输出PWM */
  TIM_OC1Init(DCMOTOR_BRUSH_TIMx, &TIM_OCInitStructure);
  /* 定时器比较输出通道1预装载配置：使能预装载 */
  TIM_OC1PreloadConfig(DCMOTOR_BRUSH_TIMx, TIM_OCPreload_Enable);
  
//  /* 定时器输出通道2模式配置 */
//  /* 设置通道2的电平跳变值，输出另外一个占空比的PWM */
//  TIM_OCInitStructure.TIM_Pulse = 1800-1;
//  /* 初始化定时器通道2输出PWM */
//  TIM_OC2Init(DCMOTOR_BRUSH_TIMx, &TIM_OCInitStructure);
//  /* 定时器比较输出通道2预装载配置：使能预装载 */
//  TIM_OC2PreloadConfig(DCMOTOR_BRUSH_TIMx, TIM_OCPreload_Enable);

//  /* 定时器输出通道3模式配置 */
//  /* 设置通道3的电平跳变值，输出另外一个占空比的PWM */
//  TIM_OCInitStructure.TIM_Pulse = 1800-1;
//  /* 初始化定时器通道3输出PWM */
//  TIM_OC3Init(DCMOTOR_BRUSH_TIMx, &TIM_OCInitStructure);
//  /* 定时器比较输出通道3预装载配置：使能预装载 */
//  TIM_OC3PreloadConfig(DCMOTOR_BRUSH_TIMx, TIM_OCPreload_Enable);
  
  /* 使能定时器重载寄存器ARR */
  TIM_ARRPreloadConfig(DCMOTOR_BRUSH_TIMx, ENABLE);

  /* 使能定时器 */
  TIM_Cmd(DCMOTOR_BRUSH_TIMx, ENABLE);
  
  /* TIM主输出使能 */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

/**
  * 函数功能: TIMx 输出PWM信号初始化
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：只要调用这个函数TIMx的三个通道就会有PWM信号输出
  */
void DCMOTOR_BRUSH_TIMx_PWM_Init(void)
{
	DCMOTOR_BRUSH_TIMx_GPIO_Config();
	DCMOTOR_BRUSH_TIMx_Configuration();	
}

/**
  * 函数功能: 直流电机控制
  * 输入参数: number：电机编号，支持三个电机驱动
  *             参数：1：对应高级定时器通道1和互补通道1
  *                   2：对应高级定时器通道2和互补通道2
  *                   3：对应高级定时器通道3和互补通道3
  *                   4：使能三个电机转动
  *                   5：三个电机都停机
  *           direction：电机方向控制
  *             参数：0：目标电机停机
  *                   1：正转
  *                   2：反转
  *           speed：电机速度调节
  *             参数：0 - 3600 ：值越大，速度越慢
  * 返 回 值: 无
  * 说    明：只要调用这个函数TIMx的三个通道就会有PWM信号输出
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
     TIM_CtrlPWMOutputs(DCMOTOR_BRUSH_TIMx,ENABLE);  // 使能输出PWM，开始转动
     break;
   case 5:
     TIM_CtrlPWMOutputs(DCMOTOR_BRUSH_TIMx,DISABLE);  // 停止输出PWM，停机
     break;
   default:
     TIM_CtrlPWMOutputs(DCMOTOR_BRUSH_TIMx,DISABLE);  // 停止输出PWM，停机
     break;
  }      
}


