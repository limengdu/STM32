/**
  ******************************************************************************
  * @file    M2006_Motor.c
  * @author  Li MengDu
  * @version V1.0
  * @date    
  * @brief   M2006无刷电机(拨弹用)，配套C610电调驱动应用函数
  ******************************************************************************
  */
  
  
/* Includes ------------------------------------------------------------------*/
#include "M2006_Motor.h"

M2006s_t M2006s[1] = {{.targetAngle = M2006_FIRSTANGLE}};


 /*******************************************************************************
 * 函 数 名         : M2006_setCurrent
 * 函数功能		    : 设置M2006电机电流值（id号为7）M2006与6623共用发送函数
 * 输    入         : iq3
 * 输    出         : 无
 * 说    明         : iqx (x:5) 对应id号电机的电流值，范围-10000~0~10000
 *                             黎孟度心血之作                                   *
 *******************************************************************************/
void M2006_setCurrent(int16_t iq3)
{
	uint8_t data[8];
	
	data[4] = iq3 >> 8;
	data[5] = iq3;

	CAN_SendData(CAN1, CAN_ID_STD, M2006_SENDID, data);
}	


/*******************************************************************************
* 函 数 名         : M2006_getInfo
* 函数功能		   : 从CAN报文中获取M2006电机信息
* 输    入         : RxMessage
* 输    出         : 无
* 说    明         : RxMessage 	CAN报文接收结构体
*                             黎孟度心血之作                                   *
*******************************************************************************/
void M2006_getInfo(CanRxMsg RxMessage)
{
	//报文id确认
	if((RxMessage.StdId < M2006_READID_START) || (RxMessage.StdId > M2006_READID_END))
		return;
	uint32_t StdId;
	StdId = RxMessage.StdId - M2006_READID_START;
	
	//解包数据，数据格式详见C610电调说明书P9
	M2006s[StdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	M2006s[StdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	M2006s[StdId].realTorque = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
	
	if(M2006s[StdId].realAngle - M2006s[StdId].lastAngle < -6000)
	{
		M2006s[StdId].turnCount++;
	}
	
	if(M2006s[StdId].lastAngle - M2006s[StdId].realAngle < -6000)
	{
		M2006s[StdId].turnCount--;
	}

	M2006s[StdId].totalAngle = M2006s[StdId].realAngle + (8192*M2006s[StdId].turnCount);
	M2006s[StdId].lastAngle =  M2006s[StdId].realAngle;
	M2006s[0].infoUpdateFrame++;
	M2006s[StdId].infoUpdateFlag = 1;
}	










