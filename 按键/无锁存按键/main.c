#include "key.h"


int main()
{
	KEY_Init();
	
	while(1)
	{
		                                                     //������汾
		if(GPIO_ReadInputDataBit(KEY_PORT,KEY_PORT_PIN)==1)  //�жϰ�����ƽ�Ƿ�Ϊ�ߵ�ƽ
			XXX;                                             //�޸ģ�����ⰴ����ƽΪ�ߵ�ƽʱ����δ���°�������ִ��XXX����
		else XXX;                                            //�޸ģ����򣨼��������£�ִ��XXX����
			
	}
}
