#ifndef __DR16_RECEIVER_H
#define __DR16_RECEIVER_H

#include "user_common.h"


#define DR16_DBUS_PACKSIZE 		18u		//接收机包大小

#define DR16_ROCKER_MAXVALUE 		660		//遥控摇杆最大值

//拨杆上中下对应值
#define DR16_SWITCH_UP			1
#define DR16_SWITCH_MID			3
#define DR16_SWITCH_DOWN		2

#define MOUSEKEY_NONE 	0x00
#define MOUSEKEY_LEFT 	0x01
#define MOUSEKEY_RIGHT 	0x02

/*-------键盘键值 Begin------*/
#define KEYBOARD_PRESSED_NONE 	0x0000

#define KEYBOARD_PRESSED_W 		0x0001
#define KEYBOARD_PRESSED_S 		0x0002
#define KEYBOARD_PRESSED_A 		0x0004
#define KEYBOARD_PRESSED_D 		0x0008
#define KEYBOARD_PRESSED_SHIFT 	0x0010
#define KEYBOARD_PRESSED_CTRL 	0x0020
#define KEYBOARD_PRESSED_Q  	0x0040
#define KEYBOARD_PRESSED_E 		0x0080

#define KEYBOARD_PRESSED_R		0x0100
#define KEYBOARD_PRESSED_F		0x0200
#define KEYBOARD_PRESSED_G		0x0400
#define KEYBOARD_PRESSED_Z		0x0800
#define KEYBOARD_PRESSED_X		0x1000
#define KEYBOARD_PRESSED_C		0x2000
#define KEYBOARD_PRESSED_V		0x4000
#define KEYBOARD_PRESSED_B		0x8000
/*-------键盘键值 End------*/

#define KEY_FULL_MATCH			0x01
#define KEY_HAVE_MATCH			0x00

extern uint8_t DR16_rxBuff[DR16_DBUS_PACKSIZE+2];
extern DR16_DBUS_DATA_t dr16_data;

extern rocker_t dr16_rocker_L,dr16_rocker_R;
extern rocker_t pcRocker;

extern ControlStatus_t ControlStatus;
void DR16_receiverInit(void);
void DR16_dataProcess(uint8_t *pData);
void Rocker_getData(float posX, float posY, rocker_t *roc);

#endif /* __DR16_RECEIVER_H */
