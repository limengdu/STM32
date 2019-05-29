/**
  ******************************************************************************
  * @file    LED.c
  * @author  Li MengDu
  * @version V1.0
  * @date    
  * @brief   LED应用函数接口
  ******************************************************************************
  */
  

/* Includes ------------------------------------------------------------------*/
#include "LED.h"


/*******************************************************************************
* 函 数 名         : LED_GPIO_Config
* 函数功能		     : LED初始化
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

	GPIO_InitStruct.GPIO_Pin = LED_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;	
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;	
	
	GPIO_Init(GPIOG, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOG,LED_Pin);
}
