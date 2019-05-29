#ifndef __USERMATH_H
#define __USERMATH_H


#define HIGH 	0x1                                             //��λ
#define LOW 	0x0                                             //��λ

#define PI 3.1415926535897932384626433832795f                 //����PI��ֵ
#define HALF_PI 1.5707963267948966192313216916398f            //����PI/2��ֵ
#define TWO_PI 6.283185307179586476925286766559f              //����2*PI��ֵ
#define DEG_TO_RAD 0.017453292519943295769236907684886f       //1��=0.017...����
#define RAD_TO_DEG 57.295779513082320876798154814105f         //1����=57.295...��
#define EULER 2.718281828459045235360287471352f               //����e��ֵ

#ifdef abs
#undef abs
#endif

#define min(a,b) ((a)<(b)?(a):(b))                            //������������С
#define max(a,b) ((a)>(b)?(a):(b))                            //�������������
#define abs(x) ((x)>0?(x):-(x))                               //�����ֵ
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))//���ڽ�ֵ��һ����ĳ��������
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5)) //��������
#define radians(deg) ((deg)*DEG_TO_RAD)                       //���Ƕ���תΪ������
#define degrees(rad) ((rad)*RAD_TO_DEG)                       //��������תΪ�Ƕ���
#define sq(x) ((x)*(x))                                       //����x��ƽ��
#define swap(a, b) { uint8_t t = a; a = b; b = t; }           //����ab��ֵ

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
