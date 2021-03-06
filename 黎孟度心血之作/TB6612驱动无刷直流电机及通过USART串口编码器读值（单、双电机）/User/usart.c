/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "stm32f10x.h"
	  	 
//使USART串口可用printf函数发送
//在usart.h文件里可更换使用printf函数的串口号

#if 1
#pragma import(__use_no_semihosting)

//标准库需要的支持函数                 
struct __FILE 
{
	int handle; 
}; 
FILE __stdout;       

//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x)
{ 
	x = x; 
} 

//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART_n->SR&0X40)==0);//循环发送,直到发送完毕   
    USART_n->DR = (u8) ch;      
	return ch;
}
#endif 


/*
USART1串口相关程序
*/
#if EN_USART1                           //USART1使用与屏蔽选择
u8 USART1_RX_BUF[USART1_REC_LEN];       //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA=0;                    //接收状态标记	  

/*******************************************************************************
* 函 数 名         : USART1_printf
* 函数功能		   : USART1专用的printf函数
* 输    入         : 无
* 输    出         : 无
* 说    明         ：当同时开启2个以上串口时，printf函数只能用于其中之一，其他
                     串口要自创独立的printf函数
                     调用方法：USART1_printf("123"); //向USART1发送字符123

*                             黎孟度心血之作                                   *
*******************************************************************************/
void USART1_printf (char *fmt, ...)
{ 
	char buffer[USART1_REC_LEN+1];  // 数据长度
	u8 i = 0;	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, USART1_REC_LEN+1, fmt, arg_ptr);
	while ((i < USART1_REC_LEN) && (i < strlen(buffer)))
	{
        USART_SendData(USART1, (u8) buffer[i++]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
	}
	va_end(arg_ptr);
}

/*******************************************************************************
* 函 数 名         : USART1_Init
* 函数功能		   : 串口1初始化并启动
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void USART1_Init(u32 bound)
{ 
    //GPIO端口设置
    GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;	 
	
	//使能USART1，GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
	
    //USART1_TX   PA9 (STM32F1系列的引脚都是不变的)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //复用推挽输出（输出需要使用复用推挽
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    //USART1_RX	  PA10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	//浮空输入（接收端只需要浮空即可）
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器
	
    //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	/*奇偶校验可以通过软件层面来滤掉干扰数据，
	仔细阅读编程手册，发现在配置奇偶校验属性后，必须要修改数据位为9位，否则PC端无法接收。
	如果将串口配置为了奇校验，且数据位为8位，那么数据位的位7将被替换为奇检验位——也就是说，原有的数据被破坏了。*/
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART1, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启ENABLE/关闭DISABLE中断
    USART_Cmd(USART1, ENABLE);                    //使能串口 
}


#endif	

/*
USART2串口相关程序
*/
#if EN_USART2   //USART2使用与屏蔽选择
u8 USART2_RX_BUF[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART2_RX_STA=0;       //接收状态标记	  

/*******************************************************************************
* 函 数 名         : USART2_printf
* 函数功能		   : USART2专用的printf函数
* 输    入         : 无
* 输    出         : 无
* 说    明         ：当同时开启2个以上串口时，printf函数只能用于其中之一，其他
                     串口要自创独立的printf函数
                     调用方法：USART2_printf("123"); //向USART2发送字符123

*                             黎孟度心血之作                                   *
*******************************************************************************/
void USART2_printf (char *fmt, ...)
{ 
	char buffer[USART2_REC_LEN+1];  // 数据长度
	u8 i = 0;	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, USART2_REC_LEN+1, fmt, arg_ptr);
	while ((i < USART2_REC_LEN) && (i < strlen(buffer)))
	{
        USART_SendData(USART2, (u8) buffer[i++]);
        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); 
	}
	va_end(arg_ptr);
}

/*******************************************************************************
* 函 数 名         : USART2_Init
* 函数功能		   : 串口2初始化并启动
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void USART2_Init(u32 bound)//串口1初始化并启动
{ 
    //GPIO端口设置
    GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
		 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); //使能UART2所在GPIOA的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //使能串口的RCC时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //设置USART2的RX接口是PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure); 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //设置USART2的TX接口是PA2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

    //USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	
	//无硬件数据流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART2, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启ENABLE/关闭DISABLE中断
    USART_Cmd(USART2, ENABLE);                    //使能串口 
	
    //Usart2 NVIC 配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器 
}


#endif	


#if EN_USART3   //如果使能了接收
u8 USART3_RX_BUF[USART3_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART3_RX_STA=0;       //接收状态标记	  

/*******************************************************************************
* 函 数 名         : USART3_printf
* 函数功能		   : USART3专用的printf函数
* 输    入         : 无
* 输    出         : 无
* 说    明         ：当同时开启2个以上串口时，printf函数只能用于其中之一，其他
                     串口要自创独立的printf函数
                     调用方法：USART3_printf("123"); //向USART3发送字符123

*                             黎孟度心血之作                                   *
*******************************************************************************/
void USART3_printf (char *fmt, ...)
{ 
	char buffer[USART3_REC_LEN+1];  // 数据长度
	u8 i = 0;	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, USART3_REC_LEN+1, fmt, arg_ptr);
	while ((i < USART3_REC_LEN) && (i < strlen(buffer))){
        USART_SendData(USART3, (u8) buffer[i++]);
        while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET); 
	}
	va_end(arg_ptr);
}

/*******************************************************************************
* 函 数 名         : USART3_Init
* 函数功能		   : 串口3初始化并启动
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void USART3_Init(u32 BaudRate)//USART3初始化并启动
{ 
   GPIO_InitTypeDef  GPIO_InitStructure;
   USART_InitTypeDef USART_InitStructure;
   NVIC_InitTypeDef  NVIC_InitStructure; 

   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); //使能UART3所在GPIOB的时钟
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //使能串口的RCC时钟

   //串口使用的GPIO口配置
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//设置USART3的RX接口是PB11
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//接口模式 浮空输入
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//设置USART3的TX接口是PB10
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//输出速度50MHz
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//接口模式 复用推挽输出
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   //配置串口
   USART_InitStructure.USART_BaudRate = BaudRate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
   USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
   USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
   //无硬件数据流控制
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

   USART_Init(USART3, &USART_InitStructure);//配置串口3
   USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//使能串口接收中断  
   //USART_ITConfig(USART3, USART_IT_TXE, ENABLE);//串口发送中断在发送数据时开启
   USART_Cmd(USART3, ENABLE);//使能串口3

   //串口中断配置
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
   NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//允许USART3中断
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//中断等级
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
}

//串口3中断服务程序（固定的函数名不能修改）
//调用方法：if(USART3_RX_STA&0xC000){ 加入数据处理程序 }//标志位是0xC000表示收到数据串完成。

#endif	




/*
a符号的作用：

%d 十进制有符号整数
%u 十进制无符号整数
%f 浮点数
%s 字符串
%c 单个字符
%p 指针的值
%e 指数形式的浮点数
%x, %X 无符号以十六进制表示的整数
%o 无符号以八进制表示的整数
%g 自动选择合适的表示法
%p 输出地址符

*/






