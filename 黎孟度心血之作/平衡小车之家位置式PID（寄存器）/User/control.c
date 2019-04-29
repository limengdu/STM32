#include "control.h"	
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
int Target_position=21000;    //初始值是10000，目标值是11000
int TIM1_UP_IRQHandler(void)  
{    
	if(TIM1->SR&0X0001)//5ms定时中断
	{   
		TIM1->SR&=~(1<<0);                            //===清除定时器1中断标志位		 
		Encoder=Read_Encoder(2);                      //===读取编码器的位置数据 初始值是10000，详见encoder.c 和encoder.h	
   		Xianfu_Pwm();                                 //===PWM限幅
		Moto1=Position_PI(Encoder,Target_position);   //===位置PI控制器
    	Set_Pwm(Moto1);                               //===赋值给PWM寄存器  
	}       	
	 return 0;	  
} 

/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int moto1)
{
			if(moto1<0)			AIN2=1,			AIN1=0;
			else 	          AIN2=0,			AIN1=1;
			PWMA=myabs(moto1);
}

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=7100;    //===PWM满幅是7200 限制在7100
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
}

/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
函数功能：位置式PI控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
在我们的位置控制闭环系统里面，只使用PI控制
pwm=Kp*e(k)+Ki*∑e(k)
**************************************************************************/
int Position_PI (int Encoder,int Target)
{ 	
   float Kp=15,Ki=0.01;	
	 static int Bias,Pwm,Integral_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Integral_bias+=Bias;	               //求出偏差的积分
	 Pwm=Kp*Bias+Ki*Integral_bias;       //位置式PI控制器
	 return Pwm;                         //增量输出
}

