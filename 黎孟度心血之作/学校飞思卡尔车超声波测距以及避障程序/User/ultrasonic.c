/*-------------------------------------------------------------------------------
文件名称：ultrasonic.c
文件描述：超声波测距模块相关功能函数。
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#include "ultrasonic.h"
#include "delay.h"
#include "stdio.h"
#include "delay.h"

u8 a;
 
u8  TIM5CH1_CAPTURE_STA=0;	                            	// 输入捕获状态	 | bit7:捕获完成标记位 | bit6：捕获到高电平标记 |	bit5~0：捕获到高电平定时器溢出的次数 |    				
u16	TIM5CH1_CAPTURE_VAL_STA,TIM5CH1_CAPTURE_VAL_END;			// 输入捕获初始值，输入捕获结束值
u8 UM_counter;
float SUM;
float MAX_Distance ,MIN_Distance;

#if EN_limengdu_code
volatile unsigned char status = 0;//程序当前状态，0,空闲 1 发送触发信号，2 等待信号返回,3 
unsigned int dis_count = 0;//脉宽长计时
volatile unsigned int distance_cm = 0;//当前距离
unsigned char t2_full_count = 0;//计数器计满次数计数
static unsigned int ultick_5ms = 0;//5ms计数器
#endif

#if EN_school_code
/*-------------------------------------------------------------------------------
函数名称：Ultrasonic_Init
函数描述：超声波模块IO初始化函数
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void Ultrasonic_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(ULTRASONIC_CLK, ENABLE);
     
	GPIO_InitStructure.GPIO_Pin 											= ULTRASONIC_TRIG;       					// 发送电平引脚
	GPIO_InitStructure.GPIO_Speed 										= GPIO_Speed_2MHz;								// GPIO_Speed_50MHz亦可
	GPIO_InitStructure.GPIO_Mode 											= GPIO_Mode_Out_PP;								// 推挽输出
	GPIO_Init(ULTRASONIC_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(ULTRASONIC_PORT, ULTRASONIC_TRIG);
	 
	GPIO_InitStructure.GPIO_Pin											  =  ULTRASONIC_ECHO;     					// 返回电平引脚
	GPIO_InitStructure.GPIO_Mode										  =  GPIO_Mode_IPD;									// 下拉输入，GPIO_Mode_IN_FLOATING亦可
	GPIO_Init(ULTRASONIC_PORT, &GPIO_InitStructure);  
	GPIO_ResetBits(ULTRASONIC_PORT,  ULTRASONIC_ECHO);	  
	
}

/*-------------------------------------------------------------------------------
函数名称：Ultrasonic_Trig
函数描述：超声波模块触发脉冲信号功能函数
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void Ultrasonic_Trig(void)
{
  TRIG_SEND = 1;               //T口发送高电平
	Delay_us(10);                //持续发送高电平10微秒
	TRIG_SEND = 0;		           //停止发送高电平
}

/*-------------------------------------------------------------------------------
函数名称：Ultrasonic_Measure
函数描述：超声波模块测距功能函数
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void Ultrasonic_Measure(void)
{   
	u32 TIM5_TC1=0;    
	float Distance, Distance_Average;
	
	Ultrasonic_Trig();                                                                    //  超声波模块发送脉冲信号
	
	if(TIM5CH1_CAPTURE_STA & 0x80)                            														//	若成功捕获到了一次高电平（最高位是1）
	{
		TIM5_TC1 = TIM5CH1_CAPTURE_STA & 0x3F;                 															//	将计数器溢出次数值赋给TIM5_TC1
		TIM5_TC1 *= 10000;					                          															//  溢出次数*重装载值=溢出计数个数总和
		
		if(TIM5CH1_CAPTURE_VAL_END >= TIM5CH1_CAPTURE_VAL_STA)															//	如果结束值大于等于初始值
		{
			TIM5_TC1 += (TIM5CH1_CAPTURE_VAL_END - TIM5CH1_CAPTURE_VAL_STA + 1);							// 得到总的高电平时间 = 溢出总计数个数 ＋ 最后一次高电平的时间
		}
		else                                               																  // 如果结束值小于初始值（说明发生至少一次溢出）                       
		{
			TIM5_TC1 += (TIM5CH1_CAPTURE_VAL_STA - TIM5CH1_CAPTURE_VAL_END + 1);							
		}
		
		TIM5CH1_CAPTURE_VAL_STA = TIM5CH1_CAPTURE_VAL_END = 0;  														// 结束值、初始值清零
		Distance = TIM5_TC1 / 1000000.0 * 340 / 2.0 * 100;      														// 距离值(单位cm) = 总的高电平时间(us) * [(340/2) /1000000 * 100]
		TIM5CH1_CAPTURE_STA = 0;			                        															// 捕获状态清零，开启下一次捕获
		
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
			Distance_Average = (SUM - MAX_Distance - MIN_Distance) / 3;												// 去掉最大值与最小值，剩余求均值
			SUM = MAX_Distance = MIN_Distance = 0;
			if((Distance_Average > 450.0) || (Distance_Average < 2.0))
			{
				printf("Ultrasonic Error \r\n");
			}
			else
			{
				printf("%.1f cm \r\n", Distance_Average);																				// 超声波测距值取小数点后1位
			}
		}
#else
		if((Distance > 450.0) || (Distance < 2.0))
		{
			printf("Ultrasonic Error \r\n");
		}
		else
		{
			printf("%.1f cm \r\n", Distance);																									// 超声波测距值取小数点后1位
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

//外部中断配置 超声波,这里没用到中断计数方式
void UltraSoundInit(void)	
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef 	EXTI_InitStructure;//定义一个外部中断相关的结构体
	NVIC_InitTypeDef NVIC_InitStructure; //定义一个中断的结构体
	
	GPIO_InitStructure.GPIO_Pin = ULTRASONIC_ECHO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ULTRASONIC_PORT , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ULTRASONIC_TRIG;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度
	GPIO_Init(ULTRASONIC_PORT , &GPIO_InitStructure);

	GPIO_EXTILineConfig(Echo_PORTSOURCE , Echo_PINSOURCE);//将GPIO口配置成外部中断 
	EXTI_InitStructure.EXTI_Line = Echo_EXITLINE;//将对应的GPIO口连接到中断线上
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//中断事件类型，下降沿
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//选择模式，中断型
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;//使能该中断
	EXTI_Init(&EXTI_InitStructure);//将配置好的参数写入寄存器
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	 //阶级为0，不可嵌套
	NVIC_InitStructure.NVIC_IRQChannel = 	Echo_IRQCH;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//主优先级0，最高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	//子优先级，最低
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//使能该模块中断
	NVIC_Init(&NVIC_InitStructure);	//中断初始化，将结构体定义的数据执行
	
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

//延时的方式读取距离值
void GetDistanceDelay(void)
{
		//发送触发信号
		Trig_SET;
		status = 1;
	  TIM_SetCounter(TIM4, 0);
	  TIM_Cmd(TIM4, ENABLE);//打开定时器
		while(TIM_GetCounter(TIM4) < 11);//延时超过10us
		status = 2;
		Trig_RESET;
		TIM_SetCounter(TIM4, 0);
	
		while(Echo == 0)//等待回向信号起始位置
		{
			if(TIM_GetCounter(TIM4) > 60000)//回应时间超出正常范围 
			{
				status = 0;
				distance_cm = 0;//失败后就后退
				printf("Ultrasonic Error \r\n");
				TIM_Cmd(TIM4, DISABLE);//关闭定时器
				return;//本次失败
			}
		}
		TIM_SetCounter(TIM4, 0);
		while(Echo == 1)//开始计算长度
		{
			int count = TIM_GetCounter(TIM4);
			if(count > 60000)//回应时间超出正常范围 
			{
				status = 0;
				distance_cm = 0;//失败后就后退
				printf("Ultrasonic Error \r\n");
				TIM_Cmd(TIM4, DISABLE);//关闭定时器
				return;//本次失败
			}
		}
		dis_count = TIM_GetCounter(TIM4);
		TIM_Cmd(TIM4, DISABLE);//关闭定时器
		distance_cm = (unsigned int)(((long)(dis_count) * 34)/2000);//声速340m/s
		printf("%d cm \r\n", distance_cm);	
		status = 0;//准备下次发送		
}
#endif




