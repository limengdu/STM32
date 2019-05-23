/*-------------------------------------------------------------------------------
文件名称：show.h
文件描述：OLED显示屏显示相关功能函数声明。   
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __SHOW_H
#define __SHOW_H

#include "stm32f10x.h"
#include "oled.h"

void OLED_Show(void);
void OLED_Speed_Show(void);
#ifdef CCD_OLED
	void OLED_DrawPoint_Shu(u8 x,u8 y,u8 t);
	void OLED_Show_CCD(void);
#endif

#endif
