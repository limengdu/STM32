/* Includes ------------------------------------------------------------------*/
#include "user_code.h"


/*******************************************************************************
* 函 数 名         : Init
* 函数功能		     : 各种初始化配置函数
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void Init(void)
{
	LED_GPIO_Config();             //LED配置
  KEY_GPIO_Config();             //按键配置
	CAN1_QuickInit();              //CAN快速初始化
	DR16_receiverInit();           //遥控器接收器配置
  delay_ms(2000);                //缓一缓
  Chassis_Init();                //步兵底盘初始化
	USART2_QuickInit(9600);        //USART2初始化，用于pc端发送，接收调试信息
	TIM6_CounterMode(89, 9999);    //定时器TIM6初始化（不知道用来干嘛？）  
}


/*******************************************************************************
* 函 数 名         : Test
* 函数功能		     : 各种功能测试函数
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void Test(void)
{
//		ANO_Send_Data_V1(-M3508s[0].targetSpeed, -M3508s[0].realSpeed,M3508s[1].targetSpeed,M3508s[1].realSpeed);
//		ANO_Send_Data_V2(-M3508s[0].targetSpeed, -M3508s[0].realSpeed,M3508s[1].targetSpeed,M3508s[1].realSpeed);
//		ANO_Send_Data_V3(-M3508s[0].targetSpeed, -M3508s[0].realSpeed,M3508s[1].targetSpeed,M3508s[1].realSpeed);

}


