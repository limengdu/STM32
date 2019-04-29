/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "encoder.h"
#include "control.h"
#include "pid.h"
#include "usart.h"


extern int Encoder_Left;                     //左编码器的脉冲计数
extern int Encoder_Right;

int Moto1;
int Moto2;

int Target_position1=0;              //设定电机1的目标速度
int Target_position2=20;              //设定电机2的目标速度

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
	//检查指定的TIM3中断发生与否
		{	
			Encoder_Left=Read_Encoder(2);           //将编码器的值赋给变量
			Encoder_Right=Read_Encoder(4);          //将编码器的值赋给变量
			
			Moto1=LocPIDCalc_PID1(Encoder_Left,Target_position1);
			MOTOR_CONTROL1(Moto1);
			Xianfu_Pwm(&Moto1,COMPARE_VALUE);
			
			Moto2=LocPIDCalc_PID2(Encoder_Right,Target_position2);
			MOTOR_CONTROL2(Moto2);
			Xianfu_Pwm(&Moto2,COMPARE_VALUE);
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIM3的中断待处理位
}


#if EN_USART1   //USART2使用与屏蔽选择
void USART1_IRQHandler(void)//串口1中断服务程序（固定的函数名不能修改）
{ 	
	u8 Res;
	//以下是字符串接收到USART1_RX_BUF[]的程序，(USART1_RX_STA&0x3FFF)是数据的长度（不包括回车）
	//当(USART1_RX_STA&0xC000)为真时表示数据接收完成，即超级终端里按下回车键。
	//在主函数里写判断if(USART1_RX_STA&0xC000)，然后读USART1_RX_BUF[]数组，读到0x0d 0x0a即是结束。
	//注意在主函数处理完串口数据后，要将USART1_RX_STA清0
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		printf("%c",Res); //把收到的数据以 a符号变量 发送回电脑		
		if((USART1_RX_STA&0x8000)==0)//接收未完成
		{			
			if(USART1_RX_STA&0x4000)//接收到了0x0d
			{				
				if(Res!=0x0a)USART1_RX_STA=0;//接收错误,重新开始
				else USART1_RX_STA|=0x8000;	//接收完成了 
			}
			else//还没收到0X0D
			{ 					
				if(Res==0x0d)USART1_RX_STA|=0x4000;
				else
				{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ; //将收到的数据放入数组
					USART1_RX_STA++;	//数据长度计数加1
					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
	} 
} 
#endif


/*******************************************************************************
* 函 数 名         : USART2_IRQHandler
* 函数功能		   : USART2中断服务函数
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
#if EN_USART2   //USART2使用与屏蔽选择
void USART2_IRQHandler(void)//串口2中断服务程序（固定的函数名不能修改）
{ 	
	u8 Res;
	//以下是字符串接收到USART2_RX_BUF[]的程序，(USART2_RX_STA&0x3FFF)是数据的长度（不包括回车）
	//当(USART2_RX_STA&0xC000)为真时表示数据接收完成，即超级终端里按下回车键。
	//在主函数里写判断if(USART2_RX_STA&0xC000)，然后读USART2_RX_BUF[]数组，读到0x0d 0x0a即是结束。
	//注意在主函数处理完串口数据后，要将USART2_RX_STA清0
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{  		
		Res =USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据
		printf("%c",Res); //把收到的数据以 a符号变量 发送回电脑		
		if((USART2_RX_STA&0x8000)==0)//接收未完成
		{			
			if(USART2_RX_STA&0x4000)//接收到了0x0d
			{				
				if(Res!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
				else USART2_RX_STA|=0x8000;	//接收完成了 
			}
			else//还没收到0X0D
			{ 					
				if(Res==0x0d)USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ; //将收到的数据放入数组
					USART2_RX_STA++;	//数据长度计数加1
					if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
	} 
} 
#endif


/*******************************************************************************
* 函 数 名         : USART3_IRQHandler
* 函数功能		   : USART3中断服务函数
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
#if EN_USART3   //USART2使用与屏蔽选择
void USART3_IRQHandler(void)
{ 	
	u8 Res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收中断
	{  
		Res =USART_ReceiveData(USART3);//读取接收到的数据
		if(Res=='S'){//判断数据是否是STOP（省略读取S）			
			USART3_RX_STA=1;//如果是STOP则标志位为1	  
		}else if(Res=='K'){//判断数据是否是OK（省略读取K）			
			USART3_RX_STA=2;//如果是OK则标志位为2	  
		}   		 
	}
} 
#endif




/********************** (C) COPYRIGHT 2019 GCUwildwolfteam *********************
**********************************END OF FILE**********************************/
