/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "encoder.h"

__IO uint32_t CaptureNumber = 0;

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/*******************************************************************************
* �� �� ��         : ENCODER_TIMx_IRQHandler
* ��������		   : TIM3�����жϷ����������������ֵ
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void ENCODER_TIMx_IRQHandler(void)
{
 	if(TIM_GetITStatus(ENCODER_TIMx, ENCODER_TIM_IT_CCx) == SET )//�����ж�
	{
		CaptureNumber++;   // ÿ��һ�������ؼ�һ
	}
	TIM_ClearITPendingBit(ENCODER_TIMx, ENCODER_TIM_IT_CCx);
}

