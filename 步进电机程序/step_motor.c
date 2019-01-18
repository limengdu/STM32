#include "step_motor.h"


void STEP_MOTOR_Init(void)//LED灯的接口初始化
{ 
	GPIO_InitTypeDef  GPIO_InitStructure; 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE); //APB2外设GPIO时钟使能      
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//启动AFIO重映射功能时钟    
    GPIO_InitStructure.GPIO_Pin = STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_C | STEP_MOTOR_D; //选择端口                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //选择IO接口工作方式       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）    
	GPIO_Init(STEP_MOTOR_PORT, &GPIO_InitStructure);
	//必须将禁用JTAG功能才能做GPIO使用
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);// 改变指定管脚的映射,完全禁用JTAG+SW-DP	
	STEP_MOTOR_OFF(); //初始状态是断电状态 			
}

void STEP_MOTOR_OFF (void)//电机断电
{
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_C | STEP_MOTOR_D);//各接口置0
}

void STEP_MOTOR_4S (u8 speed)//电机固定位置
{
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A| STEP_MOTOR_C);	//各接口置0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_D); //各接口置1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_C | STEP_MOTOR_D);
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_C); //1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_C | STEP_MOTOR_D);
	delay_ms(speed); //延时
	STEP_MOTOR_OFF(); //进入断电状态，防电机过热
}

void STEP_MOTOR_4R (u8 speed)//电机顺时针，4拍，速度快，力小
{
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_C | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A| STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_C | STEP_MOTOR_D);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_D);//1
	delay_ms(speed); //延时
	STEP_MOTOR_OFF(); //进入断电状态，防电机过热
}

void STEP_MOTOR_4L (u8 speed)//电机逆时针，4拍，速度快，力小
{
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_C | STEP_MOTOR_D);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_C | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_D);//1
	delay_ms(speed); //延时
	STEP_MOTOR_OFF(); //进入断电状态，防电机过热
}


void STEP_MOTOR_8R (u8 speed)//电机顺时针，8拍，角度小，速度慢，力大
{
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_C | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_C | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_B);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_C);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_C | STEP_MOTOR_D);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_C);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_D);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_D);//1
	delay_ms(speed); //延时
	STEP_MOTOR_OFF(); //进入断电状态，防电机过热
}

void STEP_MOTOR_8L (u8 speed)//电机逆时针，8拍，角度小，速度慢，力大
{
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_C);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_D);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_C | STEP_MOTOR_D);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_C);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_C | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_B);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_C | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C | STEP_MOTOR_D);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A);//1
	delay_ms(speed); //延时
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C);//0
	GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_D);//1
	delay_ms(speed); //延时
	STEP_MOTOR_OFF(); //进入断电状态，防电机过热
}
 

/*
选择IO接口工作方式：
GPIO_Mode_AIN 模拟输入
GPIO_Mode_IN_FLOATING 浮空输入
GPIO_Mode_IPD 下拉输入
GPIO_Mode_IPU 上拉输入
GPIO_Mode_Out_PP 推挽输出
GPIO_Mode_Out_OD 开漏输出
GPIO_Mode_AF_PP 复用推挽输出
GPIO_Mode_AF_OD 复用开漏输出
*/
