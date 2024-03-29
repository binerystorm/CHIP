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

Type gradient(float val)
{
    const float c = 4.0f;
    const float B = c * 127.5f;
    uint8_t r = clamp(roundf(c * val - B + 127.5), 0, 255);
    uint8_t g = clamp(roundf(-fabsf(-c * val + B) + 0.75 * B), 0, 255);
    uint8_t b = clamp(roundf(-c * val + B + 127.5), 0, 255);
    return Gen_Color(r, g, b);
}

