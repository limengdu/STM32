/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "user_common.h"

#define KEY_ACC_TIME     500  //ms


/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/


/*******************************************************************************
* �� �� ��         : SysTick_Handler
* ��������		     : SysTick�жϷ��������˺��������ޣ���
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void SysTick_Handler(void)
{

}


/*******************************************************************************
* �� �� ��         : CAN1_RX0_IRQHandler
* ��������		     : CAN1�жϷ�����
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void CAN1_RX0_IRQHandler(void)
{
	//�����ж�
	if(CAN_GetITStatus(CAN1, CAN_IT_FMP0)){
		CanRxMsg RxMessage;	
		CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
		M3508_getInfo(RxMessage);	
		/*printf("id %x, data %x, T%x, IL%x, IH%x, SL%x, SH%x, AL%x, AH%x\n", RxMessage.StdId, RxMessage.Data[7],
																				RxMessage.Data[6],
																				RxMessage.Data[5],
																				RxMessage.Data[4],
																				RxMessage.Data[3],
																				RxMessage.Data[2],
																				RxMessage.Data[1],
																				RxMessage.Data[0]);*/
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
	}
}


/*******************************************************************************
* �� �� ��         : USART1_IRQHandler
* ��������		     : USART1�жϷ�����(DRң����)
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		//�ر�DMA
		DMA_Cmd(USART1_RX_DMA_STREAM, DISABLE);
		
		//printf("%d\n",DMA_GetCurrDataCounter(USART1_RX_DMA_STREAM));
		//��ȡDMAbuffʣ���С���Ƿ�ƥ��
		if (DMA_GetCurrDataCounter(USART1_RX_DMA_STREAM) == 2)
		{
			//printf("%s\n", DR16_rxBuff);
			
			DR16_dataProcess(DR16_rxBuff);
		}
		
		//���ô������ݳ��ȣ�+2��֤��ȫ
    DMA_SetCurrDataCounter(USART1_RX_DMA_STREAM,DR16_DBUS_PACKSIZE+2);
		//��DMA
		DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);
		
		
		//��������жϱ�־λ
		(void)USART1->DR;
		(void)USART1->SR;
		//���ڿ����жϱ�־λ������ͨ������ĺ������
		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
}


/*******************************************************************************
* �� �� ��         : TIM6_DAC_IRQHandler
* ��������		     : TIM6�жϷ�����
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void TIM6_DAC_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) 
	{	
		
//		//ң�ع��ܵ��жϺ���
//		float Temp_Chassis_Vx = 0.0f, Temp_Chassis_Vy = 0.0f, Temp_Chassis_VOmega = 0.0f;
//		switch(ControlStatus.ControlLeft)
//		{
//			case ControlMode_ByRC:
//				Temp_Chassis_Vx = dr16_rocker_L.x*10.0f;
//				Temp_Chassis_Vy = dr16_rocker_L.y*10.0f;
//			  Temp_Chassis_VOmega = dr16_rocker_R.x*8.0f;
//			
//				break;
//			
//		  case ControlMode_ByPC:

//			 break;
//		}
//		Chassis_processing(Temp_Chassis_Vx, Temp_Chassis_Vy, Temp_Chassis_VOmega, ControlStatus.ControlLeft);
//	}

	
	//����ң�ص������ʹ����ջ��˶���������Ҫע�͵�����ң���жϲ��ַ����������У�
	//��Ȼ���ﻹû�м����ֽ���
	for(int i = 0; i<4; i++)
  {
			M3508s[i].targetSpeed = 0;    //�趨�ĸ�������ٶ�ֵ
			
			//PID����(����PID��ʽ����ѡ��)
			M3508s[i].outCurrent = Incremental_PID(&M3508s[i].pid, M3508s[i].targetSpeed, M3508s[i].realSpeed); 
			
		  //�趨�������ֵ
	    M3508_setCurrent(M3508s[0].outCurrent, M3508s[1].outCurrent, M3508s[2].outCurrent, M3508s[3].outCurrent);
	}  
	
	TIM_ClearITPendingBit(TIM6 , TIM_IT_Update);	//����жϱ�־λ
  }
}     //��������е��ԣ���ʾ�����ע�ͻ���ȡ��ע�ͼ���



/********************** (C) COPYRIGHT 2019 GCUwildwolfteam *********************
**********************************END OF FILE**********************************/
