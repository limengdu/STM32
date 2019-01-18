#ifndef __SPEEDCTROL_H_
#define __SPEEDCTROL_H_

extern unsigned char front_left_speed;
extern unsigned char front_right_speed;

void MeasureSpeed(void);
void MeasureInit(void);
void ClearMeasure(void);

#endif
