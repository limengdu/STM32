/*-------------------------------------------------------------------------------
文件名称：oled.h
文件描述：OLED显示屏相关功能函数声明。     
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __OLED_H
#define __OLED_H			  	 
#include "stm32f10x.h"
#include "stdlib.h"
#include "sys.h"

//#define SOFTWARE_OLED     			// 定义是否使用软件模拟SPI驱动OLED
#define HARDWARE_OLED     		// 定义是否使用硬件SPI驱动OLED

#ifdef HARDWARE_OLED
	#define OLED_PORT				GPIOB
	#define OLED_SCK_PIN 		GPIO_Pin_13
	#define OLED_SDA_PIN 		GPIO_Pin_15
	#define OLED_RST_PIN		GPIO_Pin_14
	#define OLED_DC_PIN 		GPIO_Pin_12
#endif
				
#define CCD_OLED

/*-----------------OLED端口定义----------------*/ 					   
/*PB15 RES复位引脚*/
#define OLED_RST_Clr() PBout(14)=0
#define OLED_RST_Set() PBout(14)=1
/*PB12 DC数据和命令控制引脚*/
#define OLED_DC_Clr() PBout(12)=0
#define OLED_DC_Set() PBout(12)=1

//使用4线串行接口时使用 
/*PB13 SPI通信的时钟引脚*/
#define OLED_SCLK_Clr()  PBout(13)=0
#define OLED_SCLK_Set()  PBout(13)=1
/*PB14 SPI通信的数据引脚（STM32->OLED）*/
#define OLED_SDIN_Clr()  PBout(15)=0
#define OLED_SDIN_Set()  PBout(15)=1
 
#define OLED_CMD  0	// 写命令
#define OLED_DATA 1	// 写数据

//OLED控制用函数
void SPIx_Init(void);
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   					   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNumber(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p);	 
#endif  
	 



