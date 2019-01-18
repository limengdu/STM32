

#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "time.h"

int main()
{
	u8 i;
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	LED_Init();
	TIM4_Init(1000,36000-1);  //��ʱ500ms
	
	while(1)
	{
		i++;
		if(i%20==0)
		{
			led1=!led1;
		}
		delay_ms(10);	
	}
}
