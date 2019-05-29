/**
  ******************************************************************************
  * @file    M3508_Motor.c
  * @author  Li MengDu
  * @version V1.0
  * @date    
  * @brief   M3508无刷电机，配套C620电调驱动应用函数接口
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "M3508_Motor.h"

M3508s_t M3508s[4];


/*******************************************************************************
* 函 数 名         : M3508_setCurrent
* 函数功能		     : 设置M3508电机电流值（id号为1~4），M3508电机只要有电流值就可以转动
* 输    入         : iq1/iq2/iq3/iq4
* 输    出         : 无
* 说    明         : iqx(x:1~4)对应id号电机的电流值，电流值的范围-16384~0~16384

*                             黎孟度心血之作                                   *
*******************************************************************************/
void M3508_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4)
{

	uint8_t data[8];
	
	//数据格式详见M3508说明书P32
	data[0] = iq1 >> 8;
	data[1] = iq1;
	data[2] = iq2 >> 8;
	data[3] = iq2;
	data[4] = iq3 >> 8;
	data[5] = iq3;
	data[6] = iq4 >> 8;
	data[7] = iq4;
	
	CAN_SendData(CAN1, CAN_ID_STD, M3508_SENDID, data);
}	


/*******************************************************************************
* 函 数 名         : M3508_getInfo
* 函数功能		     : 从CAN报文中获取M3508电机信息
* 输    入         : RxMessage：CAN报文接收结构体
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void M3508_getInfo(CanRxMsg RxMessage)
{
	//报文id确认
	if((RxMessage.StdId < M3508_READID_START) || (RxMessage.StdId > M3508_READID_END))
		return;
	uint32_t StdId;
	StdId = RxMessage.StdId - M3508_READID_START;
	
	//解包数据，数据格式详见C620电调说明书P33
	M3508s[StdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	M3508s[StdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	M3508s[StdId].realCurrent = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
	M3508s[StdId].temperture = RxMessage.Data[6];
	
	//帧率统计，数据更新标志位
	M3508s[StdId].M3508InfoUpdateFrame++;
	M3508s[StdId].M3508InfoUpdateFlag = 1;
}	





