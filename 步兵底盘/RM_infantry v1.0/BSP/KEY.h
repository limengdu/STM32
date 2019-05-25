#ifndef _KEY_H 
#define _KEY_H 

#include "user_common.h"

#define KEY_ON      1
#define KEY_OFF     0

void KEY_GPIO_Config(void);
uint8_t KEY_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);

#endif 


