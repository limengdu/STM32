/**
  ******************************************************************************
  * @file    key.c
  * @author  Li MengDu
  * @version V1.0
  * @date    
  * @brief   key应用函数接口
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "KEY.h"

/*******************************************************************************
* 函 数 名         : KEY_GPIO_Config
* 函数功能		     : 按键初始化配置
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void KEY_GPIO_Config(void)
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;	
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;		
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
}


/*******************************************************************************
* 函 数 名         : KEY_Scan
* 函数功能		     : 按键扫描
* 输    入         : GPIOx/GPIO_Pin
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
uint8_t KEY_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	if( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)== KEY_ON )
	{
		while( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)== KEY_ON );
		return KEY_ON;
	}
	else return KEY_OFF;
}


