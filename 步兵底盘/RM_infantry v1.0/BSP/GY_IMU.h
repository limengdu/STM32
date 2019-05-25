#ifndef __GY_IMU_H
#define __GY_IMU_H

#include "user_common.h"

#define GY_IMU_BUFFSIZE 	30
#define GY_IMU_PACKAGE_LENGTH 	18

extern GY_IMU_t Cloud_IMU;
extern GY_IMU_t Chassis_IMU;
extern uint8_t CV_RXBUFF[20];
extern uint8_t Cloud_GY_IMU_RXBUFF[GY_IMU_BUFFSIZE];
extern uint8_t Chassis_GY_IMU_RXBUFF[GY_IMU_BUFFSIZE];



void GY_IMU_Init(void);
void GY_IMU_getInfo(uint8_t* buff, uint16_t dataLength, GY_IMU_t* dataOut);
uint8_t GY_IMU_Checksum(uint8_t* buff);



#endif /* __GY_IMU_H */
