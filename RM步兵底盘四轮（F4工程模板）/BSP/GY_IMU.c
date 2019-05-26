/**
  ******************************************************************************
  * @file    GY_IMU.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   GY_BNO055姿态模块应用函数接口
  ******************************************************************************
  */
  
  
#include "GY_IMU.h"

//#define GY_IMU_PACKAGE_LENGTH 	18
//#define GY_IMU_BUFFSIZE 	30

uint8_t Cloud_GY_IMU_RXBUFF[GY_IMU_BUFFSIZE];
uint8_t Chassis_GY_IMU_RXBUFF[GY_IMU_BUFFSIZE];

uint8_t CV_RXBUFF[20];

GY_IMU_t Cloud_IMU;
GY_IMU_t Chassis_IMU;

/**
  * @brief  GY_IMU串口初始化
  * @param  None
  * @retval None
  */
void GY_IMU_Init(void){

	USART3_QuickInit(115200);
	USART3_RXDMA_Config((uint32_t)Cloud_GY_IMU_RXBUFF, GY_IMU_BUFFSIZE);

}



/**
  * @brief  GY_IMU数据包校验
  * @param[in]  buff	数据包
  * @retval 	0 校验失败，1校验通过
  */
uint8_t GY_IMU_Checksum(uint8_t* buff){
	uint8_t sum = 0;
	
	for(uint8_t i=0; i<GY_IMU_PACKAGE_LENGTH-1; i++){
		sum += buff[i]; 
	}
	
	if(sum == buff[GY_IMU_PACKAGE_LENGTH-1]){
		//校验通过
		return 1;
	}
	else{
		return 0;
	}
	
}

/**
  * @brief  GY_IMU数据包校验
  * @param[in]  buff	数据包 ; dataLength  数据长度 ； dataOut 获取的数据
  * @retval 	0 校验失败，1校验通过
  */
void GY_IMU_getInfo(uint8_t* buff, uint16_t dataLength, GY_IMU_t* dataOut){
	
	for(uint16_t n = 0; n < dataLength; ){
		//匹配帧头
		if( (buff[n] == 0x5A) && (buff[n+1] == 0x5A) ){
			if(GY_IMU_Checksum(&buff[n])){
				int16_t DATA[6];
				DATA[0]=(buff[n+4]<<8) | buff[n+5];
				DATA[1]=(buff[n+6]<<8) | buff[n+7];
				DATA[2]=(buff[n+8]<<8) | buff[n+9];
				DATA[3]=(buff[n+10]<<8) | buff[n+11];
				DATA[4]=(buff[n+12]<<8) | buff[n+13];
				DATA[5]=(buff[n+14]<<8) | buff[n+15];
				
				dataOut->Gyro.x = (float)DATA[0]/100;
				dataOut->Gyro.y = (float)DATA[1]/100;
				dataOut->Gyro.z = (float)DATA[2]/100;
				
				dataOut->EularDate.Yaw = (float)((uint16_t)DATA[3])/100;
				dataOut->EularDate.Pitch = (float)DATA[4]/100;
				dataOut->EularDate.Roll = (float)DATA[5]/100;
				
				dataOut->ImuDevStatus = buff[n+16];
				
				if(dataOut->EularDate.Yaw - dataOut->lastYaw < -300){
					dataOut->ImuTurnCount++;
				}
				
				if(dataOut->lastYaw - dataOut->EularDate.Yaw < -300){
					dataOut->ImuTurnCount--;
				}
				
				dataOut->lastYaw =  dataOut->EularDate.Yaw;
				
				dataOut->totalYaw = dataOut->EularDate.Yaw + (360.0f * dataOut->ImuTurnCount);
				
				dataOut->ImuInfoUpdateFrame++;
				dataOut->ImuOffLineFlag = 1;
				
				return;
			}
			else{
				n++;
			}
			
		}
		else{
			n++;
		}
	}
	
}






