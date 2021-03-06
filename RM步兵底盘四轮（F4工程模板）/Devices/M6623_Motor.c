/**
  ******************************************************************************
  * @file    M6623_Motor.c
  * @author  Li MengDu
  * @version V1.0
  * @date    
  * @brief   6623无刷电机，配套C620电调驱动应用函数
  ******************************************************************************
  */
  
  
/* Includes ------------------------------------------------------------------*/
#include "M6623_Motor.h"

M6623s_t M6623s[2];


/**
  * @brief  
  * @param  iqyaw 	对应yaw轴电机的电流值，范围-5000~0~5000
  *			iqpitch	对应pitch轴电机的电流值，范围-5000~0~5000
  * @retval None
  */
/*******************************************************************************
* 函 数 名         : M6623andM2006_setCurrent
* 函数功能		   : 设置M6623电机电流值（id号为1~4）
* 输    入         : iqyaw\iqpitch\iq7\iq8
* 输    出         : 无
* 说    明         : iqx (x:5) 对应id号电机的电流值，范围-10000~0~10000
*                             黎孟度心血之作                                   *
*******************************************************************************/
void M6623andM2006_setCurrent(int16_t iqyaw, int16_t iqpitch, int16_t iq7, int16_t iq8)
{
	uint8_t data[8];
	
	//数据格式详见说明书P32
	data[0] = iqyaw >> 8;
	data[1] = iqyaw;
	data[2] = iqpitch >> 8;
	data[3] = iqpitch;
	data[4] = iq7 >> 8;
	data[5] = iq7;
	data[6] = iq8 >> 8;
	data[7] = iq8;
	
	CAN_SendData(CAN1, CAN_ID_STD, M6623_SENDID, data);
}	


/*******************************************************************************
* 函 数 名         : M6623_calibration
* 函数功能	       : 6623校准函数
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void M6623_calibration(void)
{
	uint8_t data[8];
	
	//数据格式详见说明书P7
	data[0] = 'c';
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	data[5] = 0;
	data[6] = 0;
	data[7] = 0;
	
	CAN_SendData(CAN1, CAN_ID_STD, M6623_CALIBRATIONID, data);
}	


/*******************************************************************************
* 函 数 名         : M6623_getInfo
* 函数功能		   : 从CAN报文中获取M6623电机信息
* 输    入         : RxMessage
* 输    出         : 无
* 说    明         : *RxMessage 	CAN报文接收结构体指针
                     *info		    M6623s_t电机数组指针
*                             黎孟度心血之作                                   *
*******************************************************************************/
void M6623_getInfo(CanRxMsg RxMessage)
{
	//报文id确认
	if((RxMessage.StdId < M6623_READID_START) || (RxMessage.StdId > M6623_READID_END))
		return;
	uint32_t StdId;
	StdId = RxMessage.StdId - M6623_READID_START;
	
	//解包数据，数据格式详见6623电调说明书P8
	M6623s[StdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	M6623s[StdId].realCurrent = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	
	if(M6623s[StdId].realAngle - M6623s[StdId].lastAngle < -6000)
	{
		M6623s[StdId].turnCount++;
	}
	
	if(M6623s[StdId].lastAngle - M6623s[StdId].realAngle < -6000)
	{
		M6623s[StdId].turnCount--;
	}
	
	M6623s[StdId].lastAngle =  M6623s[StdId].realAngle;
	
	M6623s[StdId].totalAngle = M6623s[StdId].realAngle + (8192*M6623s[StdId].turnCount);
    M6623s[StdId].infoUpdateFrame++;
	M6623s[StdId].infoUpdateFlag = 1;
	
}	


/**
  * @brief  
  * @param  
  * @retval None
  */
/*******************************************************************************
* 函 数 名         : M6623_setTargetAngle
* 函数功能		   : 设定M6623电机的目标角度
* 输    入         : motorName\angle
* 输    出         : 无
* 说    明         : motorName 	电机名字 @ref M6623Name_e
		             angle		电流值，范围 0~8191 由于设置0和8191会导致电机振
					 荡，要做个限幅

*                             黎孟度心血之作                                   *
*******************************************************************************/
void M6623_setTargetAngle(M6623Name_e motorName, int32_t angle)
{
	M6623s[motorName].targetAngle = angle;
}

