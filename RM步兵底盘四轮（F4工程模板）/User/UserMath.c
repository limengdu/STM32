/**
  ******************************************************************************
  * @file    UserMath.c
  * @author   Liang Yuhao
  * @version V1.0
  * @date    
  * @brief   M2006无刷电机(拨弹用)，配套C610电调驱动应用函数接口
  ******************************************************************************
  */
#include "UserMath.h"

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

