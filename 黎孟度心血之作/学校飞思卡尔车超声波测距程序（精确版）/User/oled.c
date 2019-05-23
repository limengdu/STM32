/*-------------------------------------------------------------------------------
�ļ����ƣ�oled.c
�ļ�������OLED��ʾ����ع��ܺ�����   
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"
#include "sys.h"

// OLED���Դ�
// ��Ÿ�ʽ����.
// [0]0 1 2 3 ... 127	
// [1]0 1 2 3 ... 127	
// [2]0 1 2 3 ... 127	
// [3]0 1 2 3 ... 127	
// [4]0 1 2 3 ... 127	
// [5]0 1 2 3 ... 127	
// [6]0 1 2 3 ... 127	
// [7]0 1 2 3 ... 127 			   
u8 OLED_GRAM[128][8];	 

/*-------------------------------------------------------------------------------
�������ƣ�OLED_Refresh_Gram
����������OLED���º���
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte(0xb0+i,OLED_CMD);    // ����ҳ��ַ��0~7��
		OLED_WR_Byte(0x00,OLED_CMD);      // ������ʾλ�á��е͵�ַ
		OLED_WR_Byte(0x10,OLED_CMD);      // ������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
		{
			OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
		}
	}   
}

/*-------------------------------------------------------------------------------
�������ƣ�OLED_WR_Byte
����������OLEDд�뺯������SSD1306д��һ���ֽڣ�
���������dat:Ҫд�������/���cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
#ifdef SOFTWARE_OLED 
void OLED_WR_Byte(u8 data,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  

	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(data&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		data<<=1;   
	}				 		  
	//OLED_DC_Set();   	  
} 
#else
void OLED_WR_Byte(u8 data,u8 cmd)
{	  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2, data);
	Delay_us(2);																																			//�����ʱ�Ǳ�Ҫ�ģ���STM32f1��8M���񣬵���1us�ᵼ���Դ���³��������Ứ����ʱ�����2us��������ʱ��
		  
	//OLED_DC_Set();   	  
} 	
#endif
/*-------------------------------------------------------------------------------
�������ƣ�OLED_Display_On
����������OLED��������
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  // SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  // DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  // DISPLAY ON
}

/*-------------------------------------------------------------------------------
�������ƣ�OLED_Display_Off
����������OLED�رպ���
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  // SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  // DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  // DISPLAY OFF
}		   			 

/*-------------------------------------------------------------------------------
�������ƣ�OLED_Clear
����������OLED�������� 
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)
	{
		for(n=0;n<128;n++)
		{
			OLED_GRAM[n][i]=0X00;
		}
	}		
	OLED_Refresh_Gram();					// ������ʾ
}

/*-------------------------------------------------------------------------------
�������ƣ�OLED���㺯��
������������������ 
���������x:0~127��y:0~63��t:1 ��� 0,���;
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;// ������Χ��.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)
	{
		OLED_GRAM[x][pos]|=temp;
	}
	else 
		OLED_GRAM[x][pos]&=~temp;	    
}
	  
/*-------------------------------------------------------------------------------
�������ƣ�OLED_Fill
����������OLED��亯��
���������x1,y1,x2,y2�������ĶԽ����꣬ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63��dot:0,���;1,���	
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)
		{
			OLED_DrawPoint(x,y,dot);
		}
	}													    
	OLED_Refresh_Gram();																		// ������ʾ
}

/*-------------------------------------------------------------------------------
�������ƣ�OLED_ShowChar
����������OLED�ַ���ʾ���ܺ�������ָ��λ����ʾһ���ַ�,���������ַ���
���������x:0~127��y:0~63��mode:0,������ʾ;1,������ʾ��size:ѡ������ 16/12 
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	chr=chr-' ';																						// �õ�ƫ�ƺ��ֵ				   
    for(t=0;t<size;t++)
    {   
			if(size==12)
			{
				temp=oled_asc2_1206[chr][t];  											// ����1206����
			}
			else 
			{
				temp=oled_asc2_1608[chr][t];		 										// ����1608���� 
			}			
			for(t1=0;t1<8;t1++)
			{
				if(temp&0x80)OLED_DrawPoint(x,y,mode);
				else OLED_DrawPoint(x,y,!mode);
				temp<<=1;
				y++;
				if((y-y0) == size)
				{
					y=y0;
					x++;
					break;
				}
			}  	 
    }          
}

/*-------------------------------------------------------------------------------
�������ƣ�oled_pow
����������m^n����
���������m��n�η�
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)
	{
		result*=m;
	}    
	return result;
}				

/*-------------------------------------------------------------------------------
�������ƣ�OLED_ShowNumber
����������OLED������ʾ��������ʾ2�����֣�
���������x,y :������ꣻlen :���ֵ�λ����size:�����С��mode:ģʽ	0,���ģʽ;1,����ģʽ��num:��ֵ(0~4294967295)	 	
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void OLED_ShowNumber(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size,1);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1); 
	}
} 

/*-------------------------------------------------------------------------------
�������ƣ�OLED_ShowString
����������OLED�ַ�����ʾ����
���������x,y:������ꣻ*p:�ַ�����ʼ��ַ����16���壨8��16��
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void OLED_ShowString(u8 x,u8 y,const u8 *p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX)
				{
					x=0;
					y+=16;
				}
        if(y>MAX_CHAR_POSY)
				{
					y=x=0;
					OLED_Clear();
				}
        OLED_ShowChar(x,y,*p,12,1);	 
        x+=8;
        p++;
    }  
}	

/*-------------------------------------------------------------------------------
�������ƣ�SPI_Init
����������SPI��ʼ������
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/	
void SPIx_Init(void)
{
#ifdef HARDWARE_OLED
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);															// ʹ��PB�˿�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);															// ʹ��SPI2ʱ��

	SPI_SSOutputCmd(SPI2, ENABLE);																										// NSS---->GPIO(LED)

	GPIO_InitStructure.GPIO_Pin = OLED_SCK_PIN | OLED_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;																		// �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = OLED_RST_PIN | OLED_DC_PIN;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  																// �������														
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_PORT, &GPIO_InitStructure);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;								// ����SPIȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;																			// ���� SPI ����ģʽ:����Ϊ�� SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;																	// 8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;																				// ѡ���˴���ʱ�ӵ���̬:ʱ�ӿ���״̬Ϊ�͵�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;																			// ���ݲ����ڵ�1��ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;																					// NSS �ź����������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;								// Ԥ��Ƶ 16  (��������)36MHz/16=2.25MHz
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;																// ���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;																					// CRCֵ�������ʽ
	SPI_Init(SPI2, &SPI_InitStructure);																								// SPI2�����ʼ��
	
	SPI_Cmd(SPI2, ENABLE);																														// ʹ��SPI2
#endif
}

/*-------------------------------------------------------------------------------
�������ƣ�OLED_Init
����������OLED��ʼ������
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void OLED_Init(void)
{ 	
#ifdef SOFTWARE_OLED 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);															// ʹ��PB�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;  // �˿�����
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;																  // �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;																	// IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB,&GPIO_InitStructure);																							// �����趨������ʼ��GPIOB
#else
	SPIx_Init();
#endif

	OLED_RST_Clr();
	Delay_ms(100);
	
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD); // �ر���ʾ
	OLED_WR_Byte(0xD5,OLED_CMD); // ����ʱ�ӷ�Ƶ����,��Ƶ��
	OLED_WR_Byte(80,OLED_CMD);   // [3:0],��Ƶ����;[7:4],��Ƶ��
	OLED_WR_Byte(0xA8,OLED_CMD); // ��������·��
	OLED_WR_Byte(0X3F,OLED_CMD); // Ĭ��0X3F(1/64) 
	OLED_WR_Byte(0xD3,OLED_CMD); // ������ʾƫ��
	OLED_WR_Byte(0X00,OLED_CMD); // Ĭ��Ϊ0

	OLED_WR_Byte(0x40,OLED_CMD); // ������ʾ��ʼ�� [5:0],����.
													    
	OLED_WR_Byte(0x8D,OLED_CMD); // ��ɱ�����
	OLED_WR_Byte(0x14,OLED_CMD); // bit2������/�ر�
	OLED_WR_Byte(0x20,OLED_CMD); // �����ڴ��ַģʽ
	OLED_WR_Byte(0x02,OLED_CMD); // [1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	OLED_WR_Byte(0xA1,OLED_CMD); // ���ض�������,bit0:0,0->0;1,0->127;
	OLED_WR_Byte(0xC0,OLED_CMD); // ����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
	OLED_WR_Byte(0xDA,OLED_CMD); // ����COMӲ����������
	OLED_WR_Byte(0x12,OLED_CMD); // [5:4]����
		 
	OLED_WR_Byte(0x81,OLED_CMD); // �Աȶ�����
	OLED_WR_Byte(0xEF,OLED_CMD); // 1~255;Ĭ��0X7F (��������,Խ��Խ��)
	OLED_WR_Byte(0xD9,OLED_CMD); // ����Ԥ�������
	OLED_WR_Byte(0xf1,OLED_CMD); // [3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WR_Byte(0xDB,OLED_CMD); // ����VCOMH ��ѹ����
	OLED_WR_Byte(0x30,OLED_CMD); // [6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_WR_Byte(0xA4,OLED_CMD); // ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	OLED_WR_Byte(0xA6,OLED_CMD); // ������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ	    						   
	OLED_WR_Byte(0xAF,OLED_CMD); // ������ʾ	 
	OLED_Clear();
}  





























