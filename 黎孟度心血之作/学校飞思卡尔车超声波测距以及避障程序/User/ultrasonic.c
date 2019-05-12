/*-------------------------------------------------------------------------------
�ļ����ƣ�ultrasonic.c
�ļ����������������ģ����ع��ܺ�����
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "ultrasonic.h"
#include "delay.h"
#include "stdio.h"
#include "delay.h"

u8 a;
 
u8  TIM5CH1_CAPTURE_STA=0;	                            	// ���벶��״̬	 | bit7:������ɱ��λ | bit6�����񵽸ߵ�ƽ��� |	bit5~0�����񵽸ߵ�ƽ��ʱ������Ĵ��� |    				
u16	TIM5CH1_CAPTURE_VAL_STA,TIM5CH1_CAPTURE_VAL_END;			// ���벶���ʼֵ�����벶�����ֵ
u8 UM_counter;
float SUM;
float MAX_Distance ,MIN_Distance;

#if EN_limengdu_code
volatile unsigned char status = 0;//����ǰ״̬��0,���� 1 ���ʹ����źţ�2 �ȴ��źŷ���,3 
unsigned int dis_count = 0;//������ʱ
volatile unsigned int distance_cm = 0;//��ǰ����
unsigned char t2_full_count = 0;//������������������
static unsigned int ultick_5ms = 0;//5ms������
#endif

#if EN_school_code
/*-------------------------------------------------------------------------------
�������ƣ�Ultrasonic_Init
����������������ģ��IO��ʼ������
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void Ultrasonic_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(ULTRASONIC_CLK, ENABLE);
     
	GPIO_InitStructure.GPIO_Pin 											= ULTRASONIC_TRIG;       					// ���͵�ƽ����
	GPIO_InitStructure.GPIO_Speed 										= GPIO_Speed_2MHz;								// GPIO_Speed_50MHz���
	GPIO_InitStructure.GPIO_Mode 											= GPIO_Mode_Out_PP;								// �������
	GPIO_Init(ULTRASONIC_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(ULTRASONIC_PORT, ULTRASONIC_TRIG);
	 
	GPIO_InitStructure.GPIO_Pin											  =  ULTRASONIC_ECHO;     					// ���ص�ƽ����
	GPIO_InitStructure.GPIO_Mode										  =  GPIO_Mode_IPD;									// �������룬GPIO_Mode_IN_FLOATING���
	GPIO_Init(ULTRASONIC_PORT, &GPIO_InitStructure);  
	GPIO_ResetBits(ULTRASONIC_PORT,  ULTRASONIC_ECHO);	  
	
}

/*-------------------------------------------------------------------------------
�������ƣ�Ultrasonic_Trig
����������������ģ�鴥�������źŹ��ܺ���
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void Ultrasonic_Trig(void)
{
  TRIG_SEND = 1;               //T�ڷ��͸ߵ�ƽ
	Delay_us(10);                //�������͸ߵ�ƽ10΢��
	TRIG_SEND = 0;		           //ֹͣ���͸ߵ�ƽ
}

/*-------------------------------------------------------------------------------
�������ƣ�Ultrasonic_Measure
����������������ģ���๦�ܺ���
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void Ultrasonic_Measure(void)
{   
	u32 TIM5_TC1=0;    
	float Distance, Distance_Average;
	
	Ultrasonic_Trig();                                                                    //  ������ģ�鷢�������ź�
	
	if(TIM5CH1_CAPTURE_STA & 0x80)                            														//	���ɹ�������һ�θߵ�ƽ�����λ��1��
	{
		TIM5_TC1 = TIM5CH1_CAPTURE_STA & 0x3F;                 															//	���������������ֵ����TIM5_TC1
		TIM5_TC1 *= 10000;					                          															//  �������*��װ��ֵ=������������ܺ�
		
		if(TIM5CH1_CAPTURE_VAL_END >= TIM5CH1_CAPTURE_VAL_STA)															//	�������ֵ���ڵ��ڳ�ʼֵ
		{
			TIM5_TC1 += (TIM5CH1_CAPTURE_VAL_END - TIM5CH1_CAPTURE_VAL_STA + 1);							// �õ��ܵĸߵ�ƽʱ�� = ����ܼ������� �� ���һ�θߵ�ƽ��ʱ��
		}
		else                                               																  // �������ֵС�ڳ�ʼֵ��˵����������һ�������                       
		{
			TIM5_TC1 += (TIM5CH1_CAPTURE_VAL_STA - TIM5CH1_CAPTURE_VAL_END + 1);							
		}
		
		TIM5CH1_CAPTURE_VAL_STA = TIM5CH1_CAPTURE_VAL_END = 0;  														// ����ֵ����ʼֵ����
		Distance = TIM5_TC1 / 1000000.0 * 340 / 2.0 * 100;      														// ����ֵ(��λcm) = �ܵĸߵ�ƽʱ��(us) * [(340/2) /1000000 * 100]
		TIM5CH1_CAPTURE_STA = 0;			                        															// ����״̬���㣬������һ�β���
		
#ifdef PROCESSING_DATA	
		if(UM_counter < 5)
		{
			if(UM_counter == 0)
			{
				MIN_Distance = Distance;
			}
			MAX_Distance = max(MAX_Distance, Distance);
			MIN_Distance = max(MIN_Distance, Distance);

			SUM += Distance;
			UM_counter++;
		}
		else
		{
			UM_counter = 0;
			Distance_Average = (SUM - MAX_Distance - MIN_Distance) / 3;												// ȥ�����ֵ����Сֵ��ʣ�����ֵ
			SUM = MAX_Distance = MIN_Distance = 0;
			if((Distance_Average > 450.0) || (Distance_Average < 2.0))
			{
				printf("Ultrasonic Error \r\n");
			}
			else
			{
				printf("%.1f cm \r\n", Distance_Average);																				// ���������ֵȡС�����1λ
			}
		}
#else
		if((Distance > 450.0) || (Distance < 2.0))
		{
			printf("Ultrasonic Error \r\n");
		}
		else
		{
			printf("%.1f cm \r\n", Distance);																									// ���������ֵȡС�����1λ
		}	
#endif
	}		
}
#endif


#if EN_limengdu_code
void Time4Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);//72M / 72 = 1us
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
}

//�ⲿ�ж����� ������,����û�õ��жϼ�����ʽ
void UltraSoundInit(void)	
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef 	EXTI_InitStructure;//����һ���ⲿ�ж���صĽṹ��
	NVIC_InitTypeDef NVIC_InitStructure; //����һ���жϵĽṹ��
	
	GPIO_InitStructure.GPIO_Pin = ULTRASONIC_ECHO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ULTRASONIC_PORT , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ULTRASONIC_TRIG;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�
	GPIO_Init(ULTRASONIC_PORT , &GPIO_InitStructure);

	GPIO_EXTILineConfig(Echo_PORTSOURCE , Echo_PINSOURCE);//��GPIO�����ó��ⲿ�ж� 
	EXTI_InitStructure.EXTI_Line = Echo_EXITLINE;//����Ӧ��GPIO�����ӵ��ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�ж��¼����ͣ��½���
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//ѡ��ģʽ���ж���
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;//ʹ�ܸ��ж�
	EXTI_Init(&EXTI_InitStructure);//�����úõĲ���д��Ĵ���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	 //�׼�Ϊ0������Ƕ��
	NVIC_InitStructure.NVIC_IRQChannel = 	Echo_IRQCH;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//�����ȼ�0�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	//�����ȼ������
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ�ܸ�ģ���ж�
	NVIC_Init(&NVIC_InitStructure);	//�жϳ�ʼ�������ṹ�嶨�������ִ��
	
		Time4Init();
	  Trig_RESET;
}

void Distance(void)
{
	
	ultick_5ms++;
	if(ultick_5ms >= 15)
	{
		ultick_5ms = 0;
		GetDistanceDelay();
	}
}

//��ʱ�ķ�ʽ��ȡ����ֵ
void GetDistanceDelay(void)
{
		//���ʹ����ź�
		Trig_SET;
		status = 1;
	  TIM_SetCounter(TIM4, 0);
	  TIM_Cmd(TIM4, ENABLE);//�򿪶�ʱ��
		while(TIM_GetCounter(TIM4) < 11);//��ʱ����10us
		status = 2;
		Trig_RESET;
		TIM_SetCounter(TIM4, 0);
	
		while(Echo == 0)//�ȴ������ź���ʼλ��
		{
			if(TIM_GetCounter(TIM4) > 60000)//��Ӧʱ�䳬��������Χ 
			{
				status = 0;
				distance_cm = 0;//ʧ�ܺ�ͺ���
				printf("Ultrasonic Error \r\n");
				TIM_Cmd(TIM4, DISABLE);//�رն�ʱ��
				return;//����ʧ��
			}
		}
		TIM_SetCounter(TIM4, 0);
		while(Echo == 1)//��ʼ���㳤��
		{
			int count = TIM_GetCounter(TIM4);
			if(count > 60000)//��Ӧʱ�䳬��������Χ 
			{
				status = 0;
				distance_cm = 0;//ʧ�ܺ�ͺ���
				printf("Ultrasonic Error \r\n");
				TIM_Cmd(TIM4, DISABLE);//�رն�ʱ��
				return;//����ʧ��
			}
		}
		dis_count = TIM_GetCounter(TIM4);
		TIM_Cmd(TIM4, DISABLE);//�رն�ʱ��
		distance_cm = (unsigned int)(((long)(dis_count) * 34)/2000);//����340m/s
		printf("%d cm \r\n", distance_cm);	
		status = 0;//׼���´η���		
}
#endif




