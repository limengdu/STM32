#ifndef __M6623_MOTOR_H
#define __M6623_MOTOR_H

#include "user_common.h"

#define M6623_READID_START		0x205
#define M6623_READID_END		0x206
#define M6623_SENDID			0x1FF
#define M6623_CALIBRATIONID		0x3F0

extern M6623s_t M6623s[2];

void M6623andM2006_setCurrent(int16_t iqyaw, int16_t iqpitch, int16_t iq7, int16_t iq8);
void M6623_calibration(void);
void M6623_getInfo(CanRxMsg RxMessage);
void M6623_setTargetAngle(M6623Name_e motorName, int32_t angle);

#endif /* __M6623_MOTOR_H */
