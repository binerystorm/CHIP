#include <Arduino.h>
#include <FastLED.h>
//#include <stdint.h>
//#include <stdio.h>
//#include <assert.h>
//#include <stdlib.h>
//#include <raylib.h>

#ifndef _CHIP_H_
#define _CHIP_H_

#include "math.hpp"

#define DATACAP 37
#define CHIPCAP 6
#define WIRECAP 15
#define GLUE1CAP 6
#define GLUE2CAP 10

//#define GLUE1START 0
//#define WIRESTART GLUE1CAP
//#define CHIPSTART WIRECAP+GLUE1CAP
//#define GLUE2START WIRECAP+GLUE1CAP+CHIPCAP

//typedef Color Type;
typedef CRGB Type;


typedef struct {
    Type *data;
    size_t len;
    float color_det;
    bool on;
} Section;

typedef struct {
    Section chip;   // blue
    Section wire;   // red
    Section glue1; // green
    Section glue2; // pink
} Chip;

//#define Gen_Color(R, G, B) (Type){R, G, B, 255}  
#define Gen_Color(R, G, B) CRGB(R, G, B)  
#define HYPER(SPEED, CO) roundf((float)-(SPEED*SPEED) / (255.0f * CO) + 255.0f)

void chip_init(Chip *chip, size_t caps[4], Type *data, size_t len);
//void chip_fill_colors(Chip *chip);
// void lerp_update(const V2f *target, Section *sec, float co);
void sec_lerp_update(const float target, Section *sec, float co);
void sec_fill_color(Section *sec, Type color);
void sec_fill_gradient(Section *sec);
void sec_clear(Section *sec);
Type gradient(float val);

#endif _CHIP_H_
