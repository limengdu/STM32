#include "stm32f10x.h"
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "time.h"
#include "stm32f10x_it.h"

extern u16 time1;
extern u16 time2;

int main()
{
	u8 i;
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	LED_Init();
	TIM4_Init(1000-1,72-1);  //��ʱ1ms
	
	while(1)
	{
		i++;
        if(time1==500)  //500ms��ʱʵ���йز���
			{
				  ;
            }
        if(time2==1000) //1s��ʱʵ���йز���
			{
				;
            }
		if(i%20==0)//״̬��
		    {
				led1=!led1;
		    }
		delay_ms(10);	
	}
}
