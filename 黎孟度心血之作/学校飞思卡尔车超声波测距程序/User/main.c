/*------------------------------------------------------------------------------
文件名称：main.c
文件描述：主函数文件。   
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
------------------------------------------------------------------------------*/
/*******************************************************************************
模板制作：华南理工大学广州学院野狼队
程序名：	学校飞思卡尔车超声波测距以及避障程序
编写人：	黎孟度
编写时间：2019年5月11日
硬件支持：飞思卡尔STM32F103VET6核心板
修改日志：　　
1-	
	
说明：
 # 本程序是基于飞思卡尔STM32F103VET6核心板的硬件基础上编写的，移植需了解硬件接口
   差异。
 # 本模板是在飞思卡尔电机驱动板下实现的
 # 本模板是基于霍尔编码器实现读值的
 # 本模板增加了超声波模块测距程序，测距返回值可以通过ZigBee和串口通信查看
 # 可根据自己的需要增加或删减。
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "nvic.h"
#include "task_scheduler.h"

extern u8 *master;

int main(void)
{
	SystemInit();
	NVIC_Configuration();
	
#ifdef USE_FULL_ASSERT
  debug();
#endif
	
	Task_Init_Scheduler();
	
	while(1)
	{
		Task_Start_Scheduler();
//		OLED_Show();											// 仅用于测试OLED		
		OLED_Speed_Show();   								// 用OLED显示速度
//		Distance();
		
	}
}


#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
  

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART2, (uint8_t) ch);

  /* 循环等待直到发送结束*/
  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

/****************** (C) COPYRIGHT 2019 黎孟度心血之作 **************************
******************************END OF FILE**************************************/
