#ifndef __M2006_MOTOR_H
#define __M2006_MOTOR_H

#include "user_common.h"

#define M2006_READID_START	0x207
#define M2006_READID_END	0x207
#define M2006_SENDID		0x1FF

#define M2006_LOADANGLE		36864			/* 电机拨一个弹需要转的角度数  4.5*8191 （8孔拨弹）*/
//#define M2006_LOADANGLE		42125			/* 电机拨一个弹需要转的角度数  6*8191 （7孔拨弹）*/

//#define M2006_LOADCIRCLE	5			/* 电机拨一个弹需要转的圈数 */
//#define M2006_LOADSPEED		1800		/* 电机拨弹时的转速 */
#define M2006_FIRSTANGLE		3800		/* 电机初始位置 */

extern M2006s_t M2006s[1];

//M2006与6623共用发送函数
void M2006_setCurrent(int16_t iq3);
void M2006_getInfo(CanRxMsg RxMessage);

#endif /* __M2006_MOTOR_H */
