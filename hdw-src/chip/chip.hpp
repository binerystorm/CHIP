#include <Arduino.h>
#include <FastLED.h>
//#include <stdint.h>
//#include <stdio.h>
//#include <assert.h>
//#include <stdlib.h>
//#include <raylib.h>
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
    float x;
    float y;
} V2f;

typedef struct {
    Type *data;
    size_t len;
    V2f color_vec;
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
Type gradient(float val);
int16_t clamp(const int16_t v, const int min, const int max);
int g_max(int a, int b, int c);
void V2f_lerp(const V2f *v1, V2f *v2, float co);
void lerp_update(const V2f *target, Section *sec, float co);
void float_lerp(const float *f1, float *f2, float co);
void sec_lerp_update_1d(const float *target, Section *sec, float co);
void sec_fill(Section *sec);
void sec_fill_gradient(Section *sec);
void sec_clear(Section *sec);
void sec_lerp_update(const V2f *target, Section *sec, float co);

