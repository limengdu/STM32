/*------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ��������������ļ���   
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
------------------------------------------------------------------------------*/
/*******************************************************************************
ģ����������������ѧ����ѧԺҰ�Ƕ�
��������	ѧУ��˼����������������Լ����ϳ���
��д�ˣ�	���϶�
��дʱ�䣺2019��5��11��
Ӳ��֧�֣���˼����STM32F103VET6���İ�
�޸���־������
1-	
	
˵����
 # �������ǻ��ڷ�˼����STM32F103VET6���İ��Ӳ�������ϱ�д�ģ���ֲ���˽�Ӳ���ӿ�
   ���졣
 # ��ģ�����ڷ�˼���������������ʵ�ֵ�
 # ��ģ���ǻ��ڻ���������ʵ�ֶ�ֵ��
 # ��ģ�������˳�����ģ������򣬲�෵��ֵ����ͨ��ZigBee�ʹ���ͨ�Ų鿴
 # �ɸ����Լ�����Ҫ���ӻ�ɾ����
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
//		OLED_Show();											// �����ڲ���OLED		
		OLED_Speed_Show();   								// ��OLED��ʾ�ٶ�
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

  /* ѭ���ȴ�ֱ�����ͽ���*/
  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

/****************** (C) COPYRIGHT 2019 ���϶���Ѫ֮�� **************************
******************************END OF FILE**************************************/
