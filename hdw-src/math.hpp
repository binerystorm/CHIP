#include <Arduino.h>

#ifndef _B_MATH_H_
#define _B_MATH_H_
typedef struct {
    float x;
    float y;
} V2f;

int16_t clamp(const int16_t v, const int min, const int max);
int g_max(int a, int b, int c);
void V2f_lerp(const V2f *v1, V2f *v2, float co);
float float_lerp(const float f1, float f2, float co);
bool xor_g(bool a, bool b);
#endif _B_MATH_H_
