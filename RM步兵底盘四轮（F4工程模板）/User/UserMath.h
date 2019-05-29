#ifndef __USERMATH_H
#define __USERMATH_H


#define HIGH 	0x1                                             //置位
#define LOW 	0x0                                             //复位

#define PI 3.1415926535897932384626433832795f                 //定义PI的值
#define HALF_PI 1.5707963267948966192313216916398f            //定义PI/2的值
#define TWO_PI 6.283185307179586476925286766559f              //定义2*PI的值
#define DEG_TO_RAD 0.017453292519943295769236907684886f       //1°=0.017...弧度
#define RAD_TO_DEG 57.295779513082320876798154814105f         //1弧度=57.295...°
#define EULER 2.718281828459045235360287471352f               //定义e的值

#ifdef abs
#undef abs
#endif

#define min(a,b) ((a)<(b)?(a):(b))                            //求两变量中最小
#define max(a,b) ((a)>(b)?(a):(b))                            //求两变量中最大
#define abs(x) ((x)>0?(x):-(x))                               //求绝对值
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))//用于将值归一化到某个区间内
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5)) //四舍五入
#define radians(deg) ((deg)*DEG_TO_RAD)                       //将角度制转为弧度制
#define degrees(rad) ((rad)*RAD_TO_DEG)                       //将弧度制转为角度制
#define sq(x) ((x)*(x))                                       //定义x的平方
#define swap(a, b) { uint8_t t = a; a = b; b = t; }           //交换ab的值

#define VAL_LIMIT(val, min, max) \
do {\
if((val) <= (min))\
{\
  (val) = (min);\
}\
else if((val) >= (max))\
{\
  (val) = (max);\
}\
} while(0)\

#define getBit(value, pos) ((value >> pos) & 1)
#define setBit(value, pos) value|(1 << pos)
#define clrBit(value, pos) value&(~(1 << pos))
#define toggleBit(value, pos) value^(1 << pos)

long map(long, long, long, long, long);

#endif
