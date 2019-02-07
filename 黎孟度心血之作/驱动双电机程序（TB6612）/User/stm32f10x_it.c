/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "control.h"
#include "timer.h"

int time=0;

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : TIM1中断，PWM赋给电机
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void TIM1_IRQHandler(void)                             //TIM1中断
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //检查TIM1中断发生与否
	{
		time++;                                        //PWM值增加
		if(time<500)
			{
				MOTOR_CONTROL(time);	               //电机驱动函数
			}
		else if(time>500)
			{ 
				time=-time;                            //反转电机PWM值
				MOTOR_CONTROL(time);                   //电机驱动函数
			}
		else if(time>1000)                             //限幅
			{
				time=0;                                //PWM值清零
			}		
	}
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);        //清除TIMx的中断待处理位
}

