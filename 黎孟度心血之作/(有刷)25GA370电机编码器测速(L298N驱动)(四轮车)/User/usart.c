/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/*******************************************************************************
* 函 数 名         : DEBUG_USART_Init
* 函数功能		   : 板载调试串口参数配置
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void DEBUG_USART_Init(void)
{
  //定义结构体变量
  GPIO_InitTypeDef GPIO_InitStructure;
  //定义USART初始化结构体变量
  USART_InitTypeDef USART_InitStructure;
  //使能USART时钟
  DEBUG_USARTx_ClockCmd(DEBUG_USARTx_CLK,ENABLE);
  DEBUG_USARTx_GPIO_ClockCmd(DEBUG_USARTx_TX_CLK | DEBUG_USARTx_RX_CLK 
	                                              | RCC_APB2Periph_AFIO,ENABLE);
  //使能USART功能GPIO时钟
  
  //调试USART功能GPIO初始化
  GPIO_InitStructure.GPIO_Pin =  DEBUG_USARTx_TX_PIN;
  //设定USART发送对应IO编号
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  //设定USART发送对应IO模式：复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  //设定USART发送对应IO最大操作速度 ：GPIO_Speed_50MHz
  GPIO_Init(DEBUG_USARTx_TX_PORT, &GPIO_InitStructure); 
  //初始化USART发送对应IO   
  
  GPIO_InitStructure.GPIO_Pin = DEBUG_USARTx_RX_PIN;
  //设定USART接收对应IO编号
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //设定USART发送对应IO模式：浮空输入
  //其他没有重新赋值的成员使用与串口发送相同配置
  GPIO_Init(DEBUG_USARTx_RX_PORT, &GPIO_InitStructure);	
  //初始化USART接收对应IO
			
  //USART工作环境配置
  USART_InitStructure.USART_BaudRate = DEBUG_USARTx_BAUDRATE;
  //USART波特率:115200
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  //USART字长(有效位)：8位
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  //USART停止位：1位
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  //USART校验位：无
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  //USART硬件数据流控制(硬件信号控制传输停止)：无
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  //USART工作模式使能：允许接收和发送
  USART_Init(DEBUG_USARTx, &USART_InitStructure);
  //初始化USART
	
  USART_Cmd(DEBUG_USARTx, ENABLE);
  //使能USART
}

/*******************************************************************************
* 函 数 名         : fputc
* 函数功能		   : 重定向c库函数printf到USARTx
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
int fputc(int ch, FILE *f)
{
  USART_SendData(DEBUG_USARTx, (uint8_t) ch);
  //发送一个字节数据到调试串口
  while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);	
  //等待串口数据发送完毕	
  return (ch);
}

/*******************************************************************************
* 函 数 名         : fgetc
* 函数功能		   : 重定向c库函数getchar,scanf到USARTx
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
int fgetc(FILE *f)
{
  while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);
  //等待串口输入数据
  return (int)USART_ReceiveData(DEBUG_USARTx);
}


