#ifndef _key_H
#define _key_H

#define GPIO_KEY_RCC   RCC_APB2Periph_GPIOX                          //修改：按键所在的时钟
#define KEY_PORT_PIN   GPIO_Pin_X|GPIO_Pin_X|GPIO_Pin_X              //修改：按键对应的引脚标号
#define KEY_UP_PIN     GPIO_Pin_X                                    //修改
#define KEY_MODE       GPIO_Mode_IPU                                 //上拉输入（常规按键一般的输入模式，按键原接地）
#define KEY_SET_MODE   GPIO_Mode_IPD                                 //下拉输入（如果是一些像复位按键一样原来就接高电平的按键，可以使用下拉输入模式）
#define KEY_PORT       GPIOX                                         //修改：按键对应的IO口

#define KEY_LEFT_Pin    GPIO_Pin_X                                   //修改
#define KEY_DOWN_Pin    GPIO_Pin_X                                   //修改
#define KEY_RIGHT_Pin   GPIO_Pin_X                                   //修改
#define KEY_UP_Pin      GPIO_Pin_X                                   //修改

//使用位带操作定义
#define K_UP    PXin(X)                                              //修改
#define K_DOWN  PXin(X)                                              //修改
#define K_LEFT  PXin(X)                                              //修改
#define K_RIGHT PXin(X)                                              //修改

//读取引脚管口定义 
//#define K_UP      GPIO_ReadInputDataBit(KEY_PORT,KEY_UP_Pin)
//#define K_DOWN    GPIO_ReadInputDataBit(KEY_PORT,KEY_DOWN_Pin)
//#define K_LEFT    GPIO_ReadInputDataBit(KEY_PORT,KEY_LEFT_Pin)
//#define K_RIGHT   GPIO_ReadInputDataBit(KEY_PORT,KEY_RIGHT_Pin)

//定义各个按键值，通过按键值代表某个按键
#define KEY_UP     1
#define KEY_DOWN   2
#define KEY_LEFT   3
#define KEY_RIGHT  4  


void KEY_Init(void);

#endif




