#ifndef __FILTER_H
#define __FILTER_H


#include "stm32f4xx.h"
#include "typedef.h"


void Filter_IIRLPF(float *in,float *out, float LpfAttFactor);




#endif /* __FILTER_H */



