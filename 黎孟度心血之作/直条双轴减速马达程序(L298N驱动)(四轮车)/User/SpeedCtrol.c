/* Includes ------------------------------------------------------------------*/
#include "SpeedCtrol.h"
#include "tim.h"

//轮子直径66mm，光电码盘齿数为20，轮子周长 207mm = 20.7cm 
//程序采用判断高低电平变化次数计数，轮子转一周(相当于码盘转两周)计数次数为40
//一个计数变化表示轮子跑过的距离为 20.7/40 = 0.5175cm

unsigned char front_left_speed=0;
unsigned char front_right_speed=0;

unsigned char front_left_speed_temp=0;
unsigned char front_right_speed_temp=0;

static unsigned char front_left_io=0;
static unsigned char front_right_io=0;
static unsigned char count_5ms=0;

/*******************************************************************************
* 函 数 名         : MeasureInit
* 函数功能		   : 配置光电码盘IO口
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void MeasureInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_S_PIN;//配置使能GPIO管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度
	GPIO_Init(FRONT_RIGHT_S_GPIO , &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_S_PIN;//配置使能GPIO管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度
	GPIO_Init(FRONT_LEFT_S_GPIO , &GPIO_InitStructure); 
}

/*******************************************************************************
* 函 数 名 ：MeasureSpeed
* 函数功能 ：速度测量，计算IO变化次数，该函数必须每5ms调用一次
* 输    入 ：无
* 输    出 ：无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void MeasureSpeed(void)
{
	count_5ms++;
	if(FRONT_LEFT_S_IO != front_left_io)  //速度码盘左引脚非低电平
	{
		front_left_speed_temp++;          //计算发生了多少次电平反转
		front_left_io = FRONT_LEFT_S_IO;  //设置电平反转
	}
	
	if(FRONT_RIGHT_S_IO != front_right_io)//速度码盘右引脚非低电平
	{
		front_right_speed_temp++;
		front_right_io = FRONT_RIGHT_S_IO;
	}
	
	if(count_5ms == 100)                  //每500ms获取一次速度
	{
	  count_5ms = 0;
	  front_left_speed = front_left_speed_temp *2;//获取1s的高低电平变化次数
	  front_right_speed = front_right_speed_temp*2;
	  front_left_speed_temp = 0;
	  front_right_speed_temp = 0;
		
//	  front_left_speed = (unsigned char)(0.5175 * (double)front_left_speed + 0.5);
//	  //计算速度 cm/s 四舍五入
//	  front_right_speed = (unsigned char)(0.5175 * (double)front_right_speed + 0.5);
//	  //计算速度 cm/s 四舍五入
	  front_left_speed = (0.5175 * (double)front_left_speed + 0.5);
	  front_right_speed = (0.5175 * (double)front_right_speed + 0.5);
	}
}

/*******************************************************************************
* 函 数 名 ：ClearMeasure
* 函数功能 ：清除测量，重新开始测量
* 输    入 ：无
* 输    出 ：无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void ClearMeasure(void)
{
	count_5ms = 0;
	front_left_speed_temp = 0;
	front_right_speed_temp = 0;
}


