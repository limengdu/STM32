/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "usart.h"
#include "MemoryList.h"
#include "stm32f10x.h"
#include <stdlib.h>
#include "led.h"
#include "control.h"
#include "encoder.h"
#include "systick.h"
#include "pid.h"
#include "motor.h"
#include "datascope_gui.h"

extern EncoderType GetEncoder;
extern Get_Ready_Flag get_speed_ready_flag;
bool __Init_flag;
u16 Tim7_counter = 1;
u8 USART_RX_STA = 0;
u8 USARTx_RX_BUF[USART_REC_LEN];
u8 *master;
extern __IO u8 __PID_Start_flag;
extern float R_motor_speed;
__IO int32_t PWM_Duty;         							 								// 占空比：PWM_Duty/PWMPeriod*100%
__IO int32_t Spd_PPS;                												// 速度值 Pulse/Sample
__IO float Spd_RPM;                  												// 速度值 r/m
__IO uint8_t  __PID_Start_flag = 0;        									// PID 开始标志
unsigned char GUI_count;          													// GUI计数变量
unsigned char Send_Count; 																	// 串口需要发送的数据个数
extern PID_TypeDef sPID;
extern u8  TIM5CH1_CAPTURE_STA;	                            // 输入捕获状态		    				
extern u16 TIM5CH1_CAPTURE_VAL_STA,TIM5CH1_CAPTURE_VAL_END; // 输入捕获初始值，输入捕获结束值
u8 CCD_Threshold, CCD_Middle;


/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/


/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}


/**
  * @brief  USART2 中断处理函数
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)  
{
	u8 res;
	if(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == SET)  
	{  
		res = USART_ReceiveData(USARTx);
		
		if((res != 0x0a) && (res != 0x0d))
		{
			LED1 = ~LED1;
			USARTx_RX_BUF[0] = res;
			
			switch(USARTx_RX_BUF[0])
			{
				case 'a':	USART_SendData(USARTx, 'L'); break;
				case 'd': USART_SendData(USARTx, 'R'); break;
				case 'w': USART_SendData(USARTx, 'U'); break;
				case 's': USART_SendData(USARTx, 'D'); break;
				case 'j': USART_SendData(USARTx, 'J'); break;
				case 'k': USART_SendData(USARTx, 'H'); break;
				case ' ': USART_SendData(USARTx, 'T'); break; 
				default : break;
			}
		}
	}
}

/**
  * @brief  TIM3（编码器）溢出中断处理函数
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void) 
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update))															// 定时器产生更新中断说明编码器旋转了一圈
	{
		/*如果为向下计数模式圈数减一，否则为向上计数模式圈数加一*/
		if (TIM3 -> CR1 & 0x0010)		  
		{
			GetEncoder.rcnt3 -= 1;
		}
		
		else GetEncoder.rcnt3 += 1;
			
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);													// 清除中断和捕获标记位
	}
	
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);														// 清除中断和捕获标记位
}

/**
  * @brief  TIM5超声波回波脉宽读取中断
  * @param  None
  * @retval None
  */
void TIM5_IRQHandler(void)
{ 		    		  			      
	/*********************定时器5通道1输入捕获高电平时间**************************/
 	if((TIM5CH1_CAPTURE_STA & 0x80) == 0)      														// 还未成功捕获	
	{	   	
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)   								// 发生了更新中断（计数器溢出了）
		{		    
			if(TIM5CH1_CAPTURE_STA & 0x40)          													// 已经捕获到高电平了（STA的低六位有效的话）
			{
				if((TIM5CH1_CAPTURE_STA & 0x3F) == 0x3F)												// 低六位与Ox3F与运算，还等于0x3F，说明已满。高电平太长了
				{
					TIM5CH1_CAPTURE_STA |= 0x80;        													// 强制标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL_STA = 0XFFFF;
				}
				else 
				{
					TIM5CH1_CAPTURE_STA++;         																// 否则，（大部分情况下）标记计数器溢出一次
				}
			}	 
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)          						// 通道1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA & 0x40)		                    					  // 说明前一次是上升沿，现在捕获到一个下降沿（位6是捕获到高电平标准位）		
			{	  			
				TIM5CH1_CAPTURE_STA |= 0x80;		                     						// 标记成功捕获到一次上升沿
				TIM5CH1_CAPTURE_VAL_END = TIM_GetCapture1(TIM5);     						// 捕获到下降沿时将捕获比较寄存器的值记下
		   	TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising); 						// CC1P=0 设置为上升沿捕获，为下一次捕获做准备
			}
			else  								                               							// 还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA = 0;			                       						// 清空
				TIM5CH1_CAPTURE_VAL_STA = TIM_GetCounter(TIM5);
				TIM5CH1_CAPTURE_STA |= 0x40;		                     						// 标记捕获到了上升沿
		   	TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);						// CC1P=1 设置为下降沿捕获，开始等待下降沿的到来
			}		    
		}
 	}
  TIM_ClearITPendingBit(TIM5, TIM_IT_CC1 | TIM_IT_Update); 							// 清除中断标志位	
}

/**
  * @brief  TIM6 中断处理函数（周期循环事件）
  * @param  None
  * @retval None
  */
void TIM6_IRQHandler(void)
{	
	if(__Init_flag)
	{
		get_speed_ready_flag = Ready;
	}

  TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);													// 清除中断标志位
}

/**
  * @brief  TIM7 中断处理函数（周期循环事件）
  * @param  None
  * @retval None
  */
void TIM7_IRQHandler(void)
{	
	if(!__Init_flag)
	{
		Freescale_Device_Init();
		printf("\rHardware platform V1.0 of Mechanical Engineering Experiment Center for Freescale Intelligent Car (Made by Science)\r\n");
		printf("+>----------------------- SCI- v1.0_RC ----------------------<+ \r\n");
		printf("\r\n Freesale device initialization.\r\n");
		master = malloc(sizeof(MemoryList_STM32_Type));
	}
	
	switch(Tim7_counter)
	{
		case 10: Tim7_counter = 0; 																				// 1000us * 10 = 10ms
							 break;			
		default: break;
	}
	
	if(Tim7_counter % 10 == 0)																						// 每10ms进行PID运算
	{
		Spd_RPM = ((((float)Spd_PPS/(float)5846)*10.0f)*(float)60);	    		// 500线编码器, 26:76减速比,一圈脉冲信号是500*4*(76/26) = 5846
		if(__PID_Start_flag == 1)																					  // 计算PID结果
    {
      PWM_Duty += INC_SpdPIDCalc(Spd_RPM);
			MotorSpeedSetOne(PWM_Duty);
    }
//		printf("Spd:%d Pulse -- Spd: %.2f r/m \n",Spd_PPS,Spd_RPM);
	}
//	
//	if(Tim7_counter % 10 == 0)																						// 每100ms进行PID调试数据发送
//	{
//		DataScope_Get_Channel_Data(26, 1 );
//		DataScope_Get_Channel_Data(30.2, 2 );
//		DataScope_Get_Channel_Data(Spd_RPM, 3 ); 
//		DataScope_Get_Channel_Data(sPID.SetPoint, 4 );   
//		DataScope_Get_Channel_Data(0, 5 );
//		DataScope_Get_Channel_Data(0, 6 );
//		DataScope_Get_Channel_Data(0, 7 );
//		DataScope_Get_Channel_Data(0, 8 ); 
//		DataScope_Get_Channel_Data(0, 9 );  
//		DataScope_Get_Channel_Data(0, 10);
//		Send_Count = DataScope_Data_Generate(10);
//		for(GUI_count = 0; GUI_count < Send_Count; GUI_count++) 
//		{
//			while((USART2->SR&0X40)==0);  
//			USART2->DR = DataScope_OutPut_Buffer[GUI_count]; 
//		}
//	}
	
	Tim7_counter++;
			
  TIM_ClearITPendingBit(TIM7, TIM_FLAG_Update);													// 清除中断标志位
}

/********************** (C) COPYRIGHT 2019 GCUwildwolfteam *********************
**********************************END OF FILE**********************************/
