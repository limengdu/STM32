#include "key.h"
#include "stm32f10x.h"

/*******************************************************************************
* 函 数 名         : KEY_Init
* 函数功能		   : 按键初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                 //定义结构体变量	
	RCC_APB2PeriphClockCmd(GPIO_KEY_RCC,ENABLE);         //开启按键所在的时钟
	
	GPIO_InitStructure.GPIO_Pin=KEY_PORT_PIN;	         //选择你要设置的按键所在的IO口
	GPIO_InitStructure.GPIO_Mode=KEY_MODE;               //设置按键输入模式（上拉模式或下拉模式）

	GPIO_Init(KEY_PORT,&GPIO_InitStructure);		     //初始化GPIO
	
}






