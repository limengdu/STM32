#ifndef __RAMP_H
#define __RAMP_H


#include "user_common.h"


#define RAMP_GEN_DAFAULT \
{ \
              .count = 0, \
              .scale = 0, \
              .out = 0, \
            } \

void  ramp_init(ramp_t *ramp, int32_t scale);
float ramp_calc(ramp_t *ramp);


#endif /* __RAMP_H */



