/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "encoder.h"

__IO uint32_t CaptureNumber = 0;

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/*******************************************************************************
* 函 数 名         : ENCODER_TIMx_IRQHandler
* 函数功能		   : TIM3捕获中断服务函数，计算编码器值
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void ENCODER_TIMx_IRQHandler(void)
{
 	if(TIM_GetITStatus(ENCODER_TIMx, ENCODER_TIM_IT_CCx) == SET )//捕获中断
	{
		CaptureNumber++;   // 每来一个上升沿加一
	}
	TIM_ClearITPendingBit(ENCODER_TIMx, ENCODER_TIM_IT_CCx);
}

