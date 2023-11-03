#include <Arduino.h>
#include <FastLED.h>

#ifndef _CHIP_H_
#define _CHIP_H_

#include "math.hpp"

#define CHIP_DATACAP 37
#define CHIPCAP 6
#define WIRECAP 15
#define GLUE1CAP 6
#define GLUE2CAP 10

typedef CRGB Type;

typedef enum {
    OK = 0,
    OOB,
    OFFSET_OOB,
} SecRangeErr;

typedef struct {
    Type *data;
    size_t len;
    float temprature;
    bool on;
} Section;

typedef struct {
    Section chip;   // blue
    Section glue1; // green
    Section glue2; // pink
    Section wire;   // red
    bool broken;
} Chip;

#define Gen_Color(R, G, B) CRGB(R, G, B)  
#define HYPER(SPEED, CO) roundf((float)-(SPEED*SPEED) / (255.0f * CO) + 255.0f)

void chip_init(Chip *chip, size_t caps[4], Type *data, size_t len);
void sec_lerp_update(const float target, Section *sec, float co);
void sec_fill_color(Section *sec, Type color);
SecRangeErr sec_range_fill_color(Section *sec, size_t start_offset, size_t len, Type color);
void sec_fill_gradient(Section *sec);
void sec_clear(Section *sec);
Type gradient(float val);
void chip_animate(Chip *chip, int16_t heat);

#endif _CHIP_H_
