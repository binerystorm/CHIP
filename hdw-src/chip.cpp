#include "chip.hpp"

#define CHIP_ELEMS 4
void chip_init(Chip *chip, size_t caps[CHIP_ELEMS], Type *data, size_t len)
{

    size_t cur = 0;
    chip->chip.data = data + cur;
    cur += caps[0];
    chip->chip.len = caps[0];
    chip->chip.color_det = 0.0f;
    
    chip->glue1.data = data + cur;
    cur += caps[1];
    chip->glue1.len = caps[1];
    chip->glue1.color_det = 0.0f;
    
    chip->wire.data = data + cur;
    cur += caps[2];
    chip->wire.len = caps[2];
    chip->wire.color_det = 0.0f;

    chip->glue2.data = data + cur;
    cur += caps[3];
    chip->glue2.len = caps[3];
    chip->glue2.color_det = 0.0f;

}

void sec_lerp_update(const float target, Section *sec, float co)
{
    sec->color_det = float_lerp(target, sec->color_det, co);
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
        sec->data[i] = gradient(sec->color_det);
    }

}


void sec_fill_color(Section *sec, Type color)
{
    for(int i = 0; i < sec->len; i++) {
        sec->data[i] = color;
    }
}

SecRangeErr sec_range_fill_color(Section *sec, size_t start_offset, size_t len, Type color)
{
    if(start_offset >= sec->len) return OFFSET_OOB;
    if(start_offset + len >= sec->len) return OOB;

    for(size_t i = start_offset; i < start_offset + len; i++)
        sec->data[i] = color;

    return OK;
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

