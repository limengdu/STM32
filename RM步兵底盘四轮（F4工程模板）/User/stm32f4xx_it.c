/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "user_common.h"

#define KEY_ACC_TIME     500  //ms


/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/


/*******************************************************************************
* 函 数 名         : SysTick_Handler
* 函数功能		     : SysTick中断服务函数（此函数不可无！）
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void SysTick_Handler(void)
{

}


/*******************************************************************************
* 函 数 名         : CAN1_RX0_IRQHandler
* 函数功能		     : CAN1中断服务函数
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void CAN1_RX0_IRQHandler(void)
{
	//接收中断
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
* 函 数 名         : USART1_IRQHandler
* 函数功能		     : USART1中断服务函数(DR遥控器)
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(USART1_RX_DMA_STREAM, DISABLE);
		
		//printf("%d\n",DMA_GetCurrDataCounter(USART1_RX_DMA_STREAM));
		//获取DMAbuff剩余大小，是否匹配
		if (DMA_GetCurrDataCounter(USART1_RX_DMA_STREAM) == 2)
		{
			//printf("%s\n", DR16_rxBuff);
			
			DR16_dataProcess(DR16_rxBuff);
		}
		
		//设置传输数据长度，+2保证安全
    DMA_SetCurrDataCounter(USART1_RX_DMA_STREAM,DR16_DBUS_PACKSIZE+2);
		//打开DMA
		DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);
		
		
		//清除空闲中断标志位
		(void)USART1->DR;
		(void)USART1->SR;
		//串口空闲中断标志位并不能通过下面的函数清除
		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
}


/*******************************************************************************
* 函 数 名         : TIM6_DAC_IRQHandler
* 函数功能		     : TIM6中断服务函数
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void TIM6_DAC_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) 
	{	
		
//		//遥控功能的中断函数
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

	
	//在无遥控的情况下使电机闭环运动（首先需要注释掉上面遥控中断部分方能正常运行）
	//当然这里还没有加麦轮解算
	for(int i = 0; i<4; i++)
  {
			M3508s[i].targetSpeed = 0;    //设定四个电机的速度值
			
			//PID计算(两种PID方式供你选择)
			M3508s[i].outCurrent = Incremental_PID(&M3508s[i].pid, M3508s[i].targetSpeed, M3508s[i].realSpeed); 
			
		  //设定电机电流值
	    M3508_setCurrent(M3508s[0].outCurrent, M3508s[1].outCurrent, M3508s[2].outCurrent, M3508s[3].outCurrent);
	}  
	
	TIM_ClearITPendingBit(TIM6 , TIM_IT_Update);	//清除中断标志位
  }
}     //这个括号有点迷，提示错误就注释或者取消注释即可



/********************** (C) COPYRIGHT 2019 GCUwildwolfteam *********************
**********************************END OF FILE**********************************/
