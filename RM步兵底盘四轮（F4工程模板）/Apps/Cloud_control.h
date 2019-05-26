#ifndef __CLOUD_CONTROL_H
#define __CLOUD_CONTROL_H

#include "user_common.h"

#define Cloud_Mode_Normal		0
#define Cloud_Mode_WithIMU		1

#define Cloud_Yaw_Min			290.0f
#define Cloud_Yaw_Max			4000.0f
//#define Cloud_Yaw_Min			4000.0f
//#define Cloud_Yaw_Max			290.0f
#define Cloud_Yaw_Center	2305.0f


#define Cloud_Pitch_Min			2500.0f
#define Cloud_Pitch_Max			5000.0f
#define Cloud_Pitch_Center		4340.0f

#define M6623_AngleToDEG(ang)	ang/22.75f
#define Cloud_Yaw_delta			(Cloud_Yaw_Max - Cloud_Yaw_Min)
#define Cloud_Pitch_delta		(Cloud_Pitch_Max - Cloud_Pitch_Min)


//void Bullet_Init(void);
void Cloud_setCurrent(int16_t iqyaw, int16_t iqpitch, int16_t iq7, int16_t iq8);
void Cloud_Init(void);
void Cloud_processing(float delta_yaw, float delta_pitch, uint8_t mode);
void Cloud_processing_WithIMU(float delta_yaw, float delta_pitch, uint8_t mode);
//void Bullet_processing(float Bullet_Speed);
//void Bullet_pulling(uint8_t shoot);
void Cloud_setIMUPosForced(float posYaw, float posPitch);
float Cloud_getYawAngleWithRight(void);
float Cloud_getPitchAngleWithDown(void);
float Cloud_getYawAngleWithCenter(void);
void Cloud_setAbsPosForced(float posYaw, float posPitch);

extern Cloud_t Cloud;


#endif /* __CLOUD_CONTROL_H */



