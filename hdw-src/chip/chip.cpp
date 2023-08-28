#include "chip.hpp"

#define CHIP_ELEMS 4
void chip_init(Chip *chip, size_t caps[CHIP_ELEMS], Type *data, size_t len)
{
    //{
    //    size_t total = 0;
    //    for(int i = 0; i < CHIP_ELEMS; i++)
    //        total += caps[i];
    //    //assert(total == len);
    //}

    size_t cur = 0;
    chip->chip.data = data + cur;
    cur += caps[0];
    chip->chip.len = caps[0];
    chip->chip.color_vec = (V2f){0.0f,0.0f};
    
    chip->glue1.data = data + cur;
    cur += caps[1];
    chip->glue1.len = caps[1];
    chip->glue1.color_vec = (V2f){0.0f,0.0f};
    
    chip->wire.data = data + cur;
    cur += caps[2];
    chip->wire.len = caps[2];
    chip->wire.color_vec = (V2f){0.0f,0.0f};

    chip->glue2.data = data + cur;
    cur += caps[3];
    chip->glue2.len = caps[3];
    chip->glue2.color_vec = (V2f){0.0f,0.0f};

    // size_t cur = 0;
    // chip->glue1.data = data + cur;
    // cur += caps[2];
    // chip->glue1.len = caps[2];
    // chip->glue1.color_vec = (V2f){0.0f,0.0f};
    // chip->wire.data = data + cur;
    // cur += caps[1];
    // chip->wire.len = caps[1];
    // chip->wire.color_vec = (V2f){0.0f,0.0f};
    // chip->chip.data = data + cur;
    // cur += caps[0];
    // chip->chip.len = caps[0];
    // chip->chip.color_vec = (V2f){0.0f,0.0f};
    // chip->glue2.data = data + cur;
    // cur += caps[3];
    // chip->glue2.len = caps[3];
    // chip->glue2.color_vec = (V2f){0.0f,0.0f};

}

//void chip_fill_colors(Chip *chip)
//{
//    for(size_t i = 0; i < chip->glue1.len; i++)
//        chip->glue1.data[i] = GREEN;
//    for(size_t i = 0; i < chip->wire.len; i++)
//        chip->wire.data[i] = RED;
//    for(size_t i = 0; i < chip->chip.len; i++)
//        chip->chip.data[i] = BLUE;
//    for(size_t i = 0; i < chip->glue2.len; i++)
//        chip->glue2.data[i] = PINK;
//}

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
        float dx = ((v1->x - v2->x)/co);
        float dy = ((v1->y - v2->y)/co);
        v2->x += dx;
        v2->y += dy;
    }
}

void float_lerp(const float *f1, float *f2, float co)
{
    if(co > 0){
        *f2 += (*f1 - *f2)/co;
    }
}

void sec_lerp_update(const V2f *target, Section *sec, float co)
{
    V2f_lerp(target, &(sec->color_vec), co);
}

void sec_lerp_update_1d(const float *target, Section *sec, float co)
{
    float_lerp(target, &sec->color_vec.x, co);
}

void sec_clear(Section *sec)
{
    for(int i = 0; i < sec->len; i++) {
        sec->data[i] = Gen_Color(0, 0, 0);
    }

}

void sec_fill_gradient(Section *sec)
{
    for(int i = 0; i < sec->len; i++) {
        sec->data[i] = gradient(sec->color_vec.x);
    }

}

void sec_fill(Section *sec)
{
    for(int i = 0; i < sec->len; i++) {
        sec->data[i] = Gen_Color(sec->color_vec.x, sec->color_vec.y, sec->color_vec.y);
    }
}

Type gradient(float val)
{
    const float c = 4.0f;
    const float B = c * 127.5f;
    uint8_t r = clamp(roundf(c * val - B + 127.5), 0, 255);
    uint8_t g = clamp(roundf(-fabsf(-c * val + B) + 0.75 * B), 0, 255);
    uint8_t b = clamp(roundf(-c * val + B + 127.5), 0, 255);
    return Gen_Color(r, g, b);
}
