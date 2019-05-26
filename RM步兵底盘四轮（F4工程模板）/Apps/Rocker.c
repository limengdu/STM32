/**
  ******************************************************************************
  * @file    Rocker.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   DR16摇杆数据函数接口
  ******************************************************************************
  */
  
  
#include "Rocker.h"


/**
  * @brief  将xy坐标变成摇杆数据
  * @param[in]  posX		x坐标
  *				posY		y坐标
  * @param[out]	*roc	 	摇杆数据
  * @retval None
  */
void Rocker_getData(float posX, float posY, rocker_t *roc){
	roc->x = posX;
	roc->y = posY;
	
	roc->radian = atan2(roc->y, roc->x);
//	if (roc->radian < 0)
//		roc->radian += 2.0f * PI;
	roc->degrees = roc->radian * 180.0f / PI;
	
#if __FPU_PRESENT
	roc->distance = __sqrtf(pow(roc->x, 2) + pow(roc->y, 2));
#else
	roc->distance = sqrt(pow(roc->x, 2) + pow(roc->y, 2));
#endif
	
	if(roc->degrees>180){
      roc->distance = -roc->distance;
      //rocL->degrees = -rocL->degrees + 360.0f;
    }
}

