#ifndef __SHOOT_H
#define __SHOOT_H

#include "user_common.h"

#define FRICMOTOR_SPEEDMAX		2000
#define FRICMOTOR_SPEEDMIN		1000

//#define SHOOT_WAITSLOW		74
//#define SHOOT_WAITMIN		32
//#define SHOOT_WAITFAST		5

#define FricSpeedLevel_10MPS 	0
#define FricSpeedLevel_20MPS 	1
#define FricSpeedLevel_30MPS 	2

extern shootGun_t Gun;

extern const uint16_t FricSpeed[3];

void fric_turnOn(void);
void fric_turnOff(void);
void fricMotor_setSpeed(uint16_t speed);




void Shoot_Init(void);
void Shoot_processing(void);
 
 
#endif /* __SHOOT_H */



