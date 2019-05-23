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
__IO int32_t PWM_Duty;         							 								// ռ�ձȣ�PWM_Duty/PWMPeriod*100%
__IO int32_t Spd_PPS;                												// �ٶ�ֵ Pulse/Sample
__IO float Spd_RPM;                  												// �ٶ�ֵ r/m
__IO uint8_t  __PID_Start_flag = 0;        									// PID ��ʼ��־
unsigned char GUI_count;          													// GUI��������
unsigned char Send_Count; 																	// ������Ҫ���͵����ݸ���
extern PID_TypeDef sPID;
extern u8  TIM5CH1_CAPTURE_STA;	                            // ���벶��״̬		    				
extern u16 TIM5CH1_CAPTURE_VAL_STA,TIM5CH1_CAPTURE_VAL_END; // ���벶���ʼֵ�����벶�����ֵ
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
  * @brief  USART2 �жϴ�����
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
  * @brief  TIM3��������������жϴ�����
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void) 
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update))															// ��ʱ�����������ж�˵����������ת��һȦ
	{
		/*���Ϊ���¼���ģʽȦ����һ������Ϊ���ϼ���ģʽȦ����һ*/
		if (TIM3 -> CR1 & 0x0010)		  
		{
			GetEncoder.rcnt3 -= 1;
		}
		
		else GetEncoder.rcnt3 += 1;
			
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);													// ����жϺͲ�����λ
	}
	
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);														// ����жϺͲ�����λ
}

/**
  * @brief  TIM5�������ز������ȡ�ж�
  * @param  None
  * @retval None
  */
void TIM5_IRQHandler(void)
{ 		    		  			      
	/*********************��ʱ��5ͨ��1���벶��ߵ�ƽʱ��**************************/
 	if((TIM5CH1_CAPTURE_STA & 0x80) == 0)      														// ��δ�ɹ�����	
	{	   	
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)   								// �����˸����жϣ�����������ˣ�
		{		    
			if(TIM5CH1_CAPTURE_STA & 0x40)          													// �Ѿ����񵽸ߵ�ƽ�ˣ�STA�ĵ���λ��Ч�Ļ���
			{
				if((TIM5CH1_CAPTURE_STA & 0x3F) == 0x3F)												// ����λ��Ox3F�����㣬������0x3F��˵���������ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA |= 0x80;        													// ǿ�Ʊ�ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL_STA = 0XFFFF;
				}
				else 
				{
					TIM5CH1_CAPTURE_STA++;         																// ���򣬣��󲿷�����£���Ǽ��������һ��
				}
			}	 
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)          						// ͨ��1���������¼�
		{	
			if(TIM5CH1_CAPTURE_STA & 0x40)		                    					  // ˵��ǰһ���������أ����ڲ���һ���½��أ�λ6�ǲ��񵽸ߵ�ƽ��׼λ��		
			{	  			
				TIM5CH1_CAPTURE_STA |= 0x80;		                     						// ��ǳɹ�����һ��������
				TIM5CH1_CAPTURE_VAL_END = TIM_GetCapture1(TIM5);     						// �����½���ʱ������ȽϼĴ�����ֵ����
		   	TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising); 						// CC1P=0 ����Ϊ�����ز���Ϊ��һ�β�����׼��
			}
			else  								                               							// ��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA = 0;			                       						// ���
				TIM5CH1_CAPTURE_VAL_STA = TIM_GetCounter(TIM5);
				TIM5CH1_CAPTURE_STA |= 0x40;		                     						// ��ǲ�����������
		   	TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);						// CC1P=1 ����Ϊ�½��ز��񣬿�ʼ�ȴ��½��صĵ���
			}		    
		}
 	}
  TIM_ClearITPendingBit(TIM5, TIM_IT_CC1 | TIM_IT_Update); 							// ����жϱ�־λ	
}

/**
  * @brief  TIM6 �жϴ�����������ѭ���¼���
  * @param  None
  * @retval None
  */
void TIM6_IRQHandler(void)
{	
	if(__Init_flag)
	{
		get_speed_ready_flag = Ready;
	}

  TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);													// ����жϱ�־λ
}

/**
  * @brief  TIM7 �жϴ�����������ѭ���¼���
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
	
	if(Tim7_counter % 10 == 0)																						// ÿ10ms����PID����
	{
		Spd_RPM = ((((float)Spd_PPS/(float)5846)*10.0f)*(float)60);	    		// 500�߱�����, 26:76���ٱ�,һȦ�����ź���500*4*(76/26) = 5846
		if(__PID_Start_flag == 1)																					  // ����PID���
    {
      PWM_Duty += INC_SpdPIDCalc(Spd_RPM);
			MotorSpeedSetOne(PWM_Duty);
    }
//		printf("Spd:%d Pulse -- Spd: %.2f r/m \n",Spd_PPS,Spd_RPM);
	}
//	
//	if(Tim7_counter % 10 == 0)																						// ÿ100ms����PID�������ݷ���
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
			
  TIM_ClearITPendingBit(TIM7, TIM_FLAG_Update);													// ����жϱ�־λ
}

/********************** (C) COPYRIGHT 2019 GCUwildwolfteam *********************
**********************************END OF FILE**********************************/
