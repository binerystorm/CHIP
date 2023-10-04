#include "math.hpp"

int16_t clamp(const int16_t v, const int min, const int max)
{
    if(v <= min) return min;
    else if(v >= max) return max;
    else return v;
}

int g_max(int a, int b, int c)
{
    a = (a > b) ? a : b;
    a = (a > c) ? a : c;
    return a;
}

void V2f_lerp(const V2f *v1, V2f *v2, float co)
{
    if(co > 0){
        // pointer is used so that the values stay the same if co is 0
        float dx = ((v1->x - v2->x)/co);
        float dy = ((v1->y - v2->y)/co);
        v2->x += dx;
        v2->y += dy;
    }
}

float float_lerp(const float f1, const float f2, float co)
{
    if(co > 0){
        // pointer is used so that the values stay the same if co is 0
        return (f1 - f2)/co;
    }else{
        return f2;
    }
}
