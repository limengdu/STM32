/*-------------------------------------------------------------------------------
�ļ����ƣ�show.c
�ļ�������OLED��ʾ����ʾ������   
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "show.h"
#include "encoder.h"
#include "stdio.h"

int oled_speed_show_count =0;
u8 R_motor_speed_String[4]="0";
Get_Ready_Flag get_speed_ready_flag;
extern u8 CCD_Threshold, CCD_Middle;
extern u16 ADV[128];

/*-------------------------------------------------------------------------------
�������ƣ�OLED_Show
����������OLED��̬�ַ���������ʾ��
�����������
���ز�������
��    ע��
---------------------------------------------------------------------------------*/
void OLED_Show(void)
{
	  OLED_ShowString(0, 00, "Science-X");
		OLED_ShowString(0, 20, "TEST OK");
		OLED_ShowNumber(0, 10, 100, 3, 12);
		
		OLED_Refresh_Gram();																				// OLED��Ļˢ��
}

/*-------------------------------------------------------------------------------
�������ƣ�OLED_Speed_Show
����������OLED������ʾ���ܺ�����
�����������
���ز�������
��    ע��
---------------------------------------------------------------------------------*/
void OLED_Speed_Show(void)   						
{
	if(get_speed_ready_flag == Ready)
	{
		Speed_Measurement(3);
		get_speed_ready_flag = UN_Ready;
	}
	
	oled_speed_show_count++;
	if(oled_speed_show_count == 1000)
	{
		oled_speed_show_count = 0;

#ifdef CCD_OLED
//	  OLED_ShowString(0, 00, "Speed r/s:");
//		//OLED_ShowNumber(4,12,R_motor_speed,11 ,12);
//		sprintf((char*)R_motor_speed_String, "%f", R_motor_speed); 
//		OLED_ShowString(50, 10, R_motor_speed_String);
//	  OLED_ShowString(90, 10, "rad/s");
//		
//		OLED_ShowString(0, 20, "vehicle_speed:");
//		OLED_ShowNumber(0, 32, (u32)V_motor_speed, 14, 12);
//	  OLED_ShowString(90, 32, "mm/s");
		
		OLED_Show_CCD(); 
	  OLED_ShowString(0, 40, "Threshold:");
  	OLED_ShowNumber(80, 40, CCD_Threshold, 4, 12);
  	OLED_ShowString(0, 50, "Middle:");
  	OLED_ShowNumber(60, 50, CCD_Middle, 4, 12);
		
#else
		OLED_ShowString(0, 00, "Speed r/s:");
		//OLED_ShowNumber(4, 12, R_motor_speed, 11 ,12);
		sprintf((char*)R_motor_speed_String, "%f", R_motor_speed); 
		OLED_ShowString(50, 12, R_motor_speed_String);
	  OLED_ShowString(90, 12, "rad/s");
		
		OLED_ShowString(0, 30, "vehicle_speed:");
		OLED_ShowNumber(0, 42, (u32)V_motor_speed, 14, 12);
	  OLED_ShowString(90, 42, "mm/s");
#endif
		
		OLED_Refresh_Gram();																				 // OLED��Ļˢ��
	}
}

#ifdef CCD_OLED
/*-------------------------------------------------------------------------------
�������ƣ�OLED_DrawPoint_Shu
����������OLED��ʾ�����ܺ�����
���������x,y:������ꣻtΪ�Ƿ�滭��Ӧ����
���ز�������
��    ע��
---------------------------------------------------------------------------------*/
void OLED_DrawPoint_Shu(u8 x, u8 y, u8 t)
{ 
	u8 i=0;
  OLED_DrawPoint(x,y,t);
	OLED_DrawPoint(x,y,t);
	for(i = 0;i<8; i++)
  {
		OLED_DrawPoint(x,y+i,t);
  }
}
/*-------------------------------------------------------------------------------
�������ƣ�OLED_Show_CCD
����������OLED��ʾ������λ�ù��ܺ�����
�����������
���ز�������
��    ע��
---------------------------------------------------------------------------------*/
void OLED_Show_CCD(void)
{ 
	u8 i,t;
	for(i = 0;i<128; i++)
  {
		if(ADV[i] < CCD_Threshold) t=1; else t=0;
		OLED_DrawPoint_Shu(i,0,t);
  }
}
#endif
