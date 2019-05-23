/*-------------------------------------------------------------------------------
文件名称：ccd.h
文件描述：线性CCD模块相关宏及其功能函数声明。    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __CCD_H
#define __CCD_H	

#include "sys.h"

#define TSL_CLK   PCout(1)   //CLK 
#define TSL_SI    PCout(2)   //SI  

void Dly_us(void);
void RD_TSL(void) ;   
void CCD_Init(void);
void Find_CCD_Middle(void);

#endif
