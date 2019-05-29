/**
  ******************************************************************************
  * @file    DR16_Receiver.c
  * @author  Li MengDu
  * @version V1.0
  * @date    
  * @brief   DR16接收机应用函数接口
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <Math.h>
#include "DR16_Receiver.h"

uint8_t DR16_rxBuff[DR16_DBUS_PACKSIZE+2]; 	//接收buff
DR16_DBUS_DATA_t dr16_data;

ControlStatus_t ControlStatus;

rocker_t dr16_rocker_L,dr16_rocker_R;
rocker_t pcRocker;

//ControlStatus_t ControlStatus;


/*******************************************************************************
* 函 数 名         : DR16_receiverInit
* 函数功能		     : DR16接收机初始化
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void DR16_receiverInit(void)
{
	USART1_QuickInit(100000);                                         //使用USART1传输接收数据，设置波特率
	USART1_RXDMA_Config((uint32_t)DR16_rxBuff, DR16_DBUS_PACKSIZE+2);	//+2保证安全
  //设置传输地址和数据大小
}


/*******************************************************************************
* 函 数 名         : DR16_receiverInit
* 函数功能		     : 产生X，Y坐标
* 输    入         : posX posY 键盘或遥控的X Y数值/ *roc
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void Rocker_getData(float posX, float posY, rocker_t *roc)
{
	roc->x = posX;
	roc->y = posY;
	roc->radian = atan2(roc->y, roc->x);
}


/*******************************************************************************
* 函 数 名         : DR16_dataProcess
* 函数功能		     : DR16接收数据处理
* 输    入         : pData			接收buff数据指针
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void DR16_dataProcess(uint8_t *pData)
{
	if (pData == NULL)
	{
		return;
	}
	dr16_data.rc.ch0 = (pData[0] | (pData[1] << 8)) & 0x07FF;
	dr16_data.rc.ch1 = ((pData[1] >> 3) | (pData[2] << 5)) & 0x07FF;
	dr16_data.rc.ch2 = ((pData[2] >> 6) | (pData[3] << 2) | (pData[4] << 10)) & 0x07FF;
	dr16_data.rc.ch3 = ((pData[4] >> 1) | (pData[5] << 7)) & 0x07FF;
	dr16_data.rc.s_left = ((pData[5] >> 4) & 0x000C) >> 2;
	dr16_data.rc.s_right = ((pData[5] >> 4) & 0x0003);
	dr16_data.mouse.x = (pData[6]) | (pData[7] << 8);
	dr16_data.mouse.y = (pData[8]) | (pData[9] << 8);
	dr16_data.mouse.z = (pData[10]) | (pData[11] << 8);
	dr16_data.mouse.keyLeft = pData[12];
	dr16_data.mouse.keyRight = pData[13];
	dr16_data.keyBoard.key_code = pData[14]| (pData[15] << 8);
	//your control code ….
	
	dr16_data.DR16InfoUpdateFrame++;
	
	dr16_data.rc.ch0 -=1024;
	dr16_data.rc.ch1 -=1024;
	dr16_data.rc.ch2 -=1024;
	dr16_data.rc.ch3 -=1024;
	
	/* prevent remote control zero deviation */
	if(dr16_data.rc.ch0 <= 20 && dr16_data.rc.ch0 >= -20)
		dr16_data.rc.ch0 = 0;
	if(dr16_data.rc.ch1 <= 20 && dr16_data.rc.ch1 >= -20)
		dr16_data.rc.ch1 = 0;
	if(dr16_data.rc.ch2 <= 20 && dr16_data.rc.ch2 >= -20)
		dr16_data.rc.ch2 = 0;
	if(dr16_data.rc.ch3 <= 20 && dr16_data.rc.ch3 >= -20)
		dr16_data.rc.ch3 = 0;
	
  ControlStatus.ControlLeft=dr16_data.rc.s_left;
	ControlStatus.ControlRight=dr16_data.rc.s_right;
	
	Rocker_getData(dr16_data.rc.ch2, dr16_data.rc.ch3, &dr16_rocker_L);
	Rocker_getData(dr16_data.rc.ch0, dr16_data.rc.ch1, &dr16_rocker_R);
}
	
	
	
	



