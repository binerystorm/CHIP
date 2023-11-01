#include "chip.hpp"
#include "control.hpp"

#define CHIP_ELEMS 4
void chip_init(Chip *chip, size_t caps[CHIP_ELEMS], Type *data, size_t len)
{

    size_t cur = 0;
    chip->chip.data = data + cur;
    cur += caps[0];
    chip->chip.len = caps[0];
    chip->chip.temprature = 0.0f;
    
    chip->glue1.data = data + cur;
    cur += caps[1];
    chip->glue1.len = caps[1];
    chip->glue1.temprature = 0.0f;
    
    chip->wire.data = data + cur;
    cur += caps[2];
    chip->wire.len = caps[2];
    chip->wire.temprature = 0.0f;

    chip->glue2.data = data + cur;
    cur += caps[3];
    chip->glue2.len = caps[3];
    chip->glue2.temprature = 0.0f;

}

void chip_fill_color(Chip *chip, Type color)
{
    sec_fill_color(&(chip->chip), color);
    sec_fill_color(&(chip->wire), color);
    sec_fill_color(&(chip->glue1), color);
    sec_fill_color(&(chip->glue2), color);
}

void chip_reset(Chip *chip)
{
    chip->chip.temprature = 0;
    chip->wire.temprature = 0;
    chip->glue1.temprature = 0;
    chip->glue2.temprature = 0;
}

void chip_animate(Chip *chip, int16_t heat)
{
    if (chip->broken)
        return;
    
    if (chip->chip.temprature >= 254){
        chip->broken = true;
        chip_reset(chip);
        chip_fill_color(chip, CRGB::Black);
    }

    sec_lerp_update(heat, &chip->chip, 700.0f);
    sec_lerp_update(heat, &chip->glue1, 475.0f);
    sec_lerp_update(heat, &chip->glue2, 115.0f);
}

void sec_lerp_update(const float target, Section *sec, float co)
{
    sec->temprature = float_lerp(target, sec->temprature, co);
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
        sec->data[i] = gradient(sec->temprature);
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

