//��ģ��ʵ�ֵĲ����ǣ���һ�ΰ������������ٰ�һ�ΰ���������
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "key.h"


int main()
{
	SysTick_Init(72);
	LED_Init();
	KEY_Init();
	
	while(1)
	{
		if(GPIO_ReadInputDataBit(KEY_PORT,GPIO_Pin_X)==0)        //�޸ģ���ȡ����X���ŵ�ƽ״̬������������ʱ
		{
			delay_ms(20);	                                     //������е����ʱ��Լ10~20ms��������ʱ20ms������
			if(GPIO_ReadInputDataBit(KEY_PORT,GPIO_Pin_X)==1)    //�޸ģ���������֮�����жϰ���X���ŵ�ƽ״̬�����ɿ�����ʱ��ִ�����²���
			{
				PXout(X)=!PXout(X);                              //�޸ģ������ʾȡ������������֮ǰΪ�͵�ƽ״̬���Ϊ�ߵ�ƽ������֮ǰΪ�ߵ�ƽ״̬���Ϊ�͵�ƽ
			}
		}	
	}
}
