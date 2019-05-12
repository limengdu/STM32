/*-------------------------------------------------------------------------------
�ļ����ƣ�oled.h
�ļ�������OLED��ʾ����ع��ܺ���������     
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __OLED_H
#define __OLED_H			  	 
#include "stm32f10x.h"
#include "stdlib.h"
#include "sys.h"

//#define SOFTWARE_OLED     			// �����Ƿ�ʹ�����ģ��SPI����OLED
#define HARDWARE_OLED     		// �����Ƿ�ʹ��Ӳ��SPI����OLED

#ifdef HARDWARE_OLED
	#define OLED_PORT				GPIOB
	#define OLED_SCK_PIN 		GPIO_Pin_13
	#define OLED_SDA_PIN 		GPIO_Pin_15
	#define OLED_RST_PIN		GPIO_Pin_14
	#define OLED_DC_PIN 		GPIO_Pin_12
#endif
				
#define CCD_OLED

/*-----------------OLED�˿ڶ���----------------*/ 					   
/*PB15 RES��λ����*/
#define OLED_RST_Clr() PBout(14)=0
#define OLED_RST_Set() PBout(14)=1
/*PB12 DC���ݺ������������*/
#define OLED_DC_Clr() PBout(12)=0
#define OLED_DC_Set() PBout(12)=1

//ʹ��4�ߴ��нӿ�ʱʹ�� 
/*PB13 SPIͨ�ŵ�ʱ������*/
#define OLED_SCLK_Clr()  PBout(13)=0
#define OLED_SCLK_Set()  PBout(13)=1
/*PB14 SPIͨ�ŵ��������ţ�STM32->OLED��*/
#define OLED_SDIN_Clr()  PBout(15)=0
#define OLED_SDIN_Set()  PBout(15)=1
 
#define OLED_CMD  0	// д����
#define OLED_DATA 1	// д����

//OLED�����ú���
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
	 



