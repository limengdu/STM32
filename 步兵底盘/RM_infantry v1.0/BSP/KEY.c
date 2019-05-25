/**
  ******************************************************************************
  * @file    key.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   key应用函数接口
  ******************************************************************************
  */

#include "KEY.h"


void KEY_GPIO_Config(void)
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;	
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;		
	
	GPIO_Init(GPIOD, &GPIO_InitStruct);	

	
}


uint8_t KEY_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	if( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)== KEY_ON )
	{
		while( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)== KEY_ON );
			return KEY_ON;
	}
	else return KEY_OFF;
		
}


