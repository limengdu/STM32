#include "moto.h"

/*******************************************************************************
* 函 数 名         : MOTO_Config
* 函数功能		   : 驱动tb6612对应电机IO配置
* 输    入         : 无
* 输    出         : 无
* 说    明         ：接线及电机转动状态表（默认状态下注释B电机IO）：
________________________________________________________________________________
    |  AIN1(PB11)  AIN2(PB12)  PWMA(PA8)   A01       A02       电机转动方向  |
    |  高电平(1)   低电平(0)      1      电机正极  电机负极    正转(顺时针)  |
    |  BIN1(PB14)  BIN2(PB15)  PWMB(PB13)  B01       B02       电机转动方向  |
    |  高电平(1)   低电平(0)      1      电机正极  电机负极    正转(顺时针)  |
________________________________________________________________________________
*                             黎孟度心血之作                                   *
*******************************************************************************/
void MOTO_Config(void)
{
	//定义一个GPIO_InitTypeDef类型的结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//开启GPIOB的外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	
	//选择要控制的GPIOB引脚													   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 
	                              | GPIO_Pin_14 | GPIO_Pin_15
	                              ;
	//设置引脚模式为通用推挽输出
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	//设置引脚速率为50MHz
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	//调用库函数，初始化GPIOB
  	GPIO_Init(GPIOB, &GPIO_InitStructure);		  

	//低电平，确保初始状态下电机处于停止状态
	GPIO_SetBits(GPIOB,GPIO_Pin_11 | GPIO_Pin_12);
	GPIO_SetBits(GPIOB,GPIO_Pin_14 | GPIO_Pin_15);
}




