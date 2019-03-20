/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "motor.h"
#include "tim.h"
#include "SpeedCtrol.h"

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/*******************************************************************************
* 函 数 名         : TIM2_IRQHandler
* 函数功能		   : 实现小车运动
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {                                     //检查指定的TIM2中断发生与否
        tick_1ms++;
				if(tick_1ms >= 10)        //计算周期为1ms，这里判断是否达到1ms
				{
					tick_1ms = 0;         //置0重新计时
					speed_count++;
					tick_5ms++;
				    if(speed_count >= 50) //50ms为一个占空比周期
					{
						speed_count = 0;  //置0重新计算周期
					}
					CarMove();          //小车运动配置函数
					CarGo();            //小车前进运动函数
//					CarBack();          //如需要小车后退，取消注释此语句
//					CarLeft();          //如需要小车原地左转，取消注释此语句
//                  CarRight();         //如需要小车原地右转，取消注释此语句
					MeasureSpeed();     //测速
				}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除中断Tim2待处理位
    }
}

/********************** (C) COPYRIGHT 2019 GCUwildwolfteam *********************
**********************************END OF FILE**********************************/
