/**
  ******************************************************************************
  * @file    NVIC.c
  * @author Li MengDu
  * @version V1.0
  * @date    
  * @brief   NVIC中断优先级应用函数接口
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "NVIC.h"


/*******************************************************************************
* 函 数 名         : NVIC_Config
* 函数功能		     : NVIC中断优先级配置
* 输    入         : IRQChannel 	 中断源，参考"stm32f4xx.h", 196行、（中断服务函数名在.s文件里）
                     MainPriority	 主优先级
                     SubPriority	 抢占式优先级
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void NVIC_Config(uint16_t IRQChannel, uint16_t MainPriority, uint16_t SubPriority)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;
	//设置主优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = MainPriority;
	//设置抢占式优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
