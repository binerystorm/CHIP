#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define BYTE_LEN 254

typedef struct {
    int16_t r;
    int16_t g;
    int16_t b;
}RGB;

int16_t clamp(const int16_t v, const int min, const int max)
{
    if(v <= min) return min;
    else if(v >= max) return max;
    else return v;
}

int max(int a, int b, int c)
{
    a = (a > b) ? a : b;
    a = (a > c) ? a : c;
    return a;
}

Color RGB2RGBA2(RGB c)
{
    Color ret = {0};
    ret.r = c.r;
    ret.g = c.g;
    ret.b = c.b;
    ret.a = 255;
    return ret;
}

Color RGB2RGBA(RGB c)
{
    Color ret = {0};
    ret.r = clamp(c.r, 50, 255);
    ret.g = clamp(c.g, 50, 255);
    ret.b = clamp(c.b, 50, 255);
    ret.a = max(c.r, c.g, c.b);
    return ret;
}

void color_update_exp(RGB *color, float C)
{
    color->r = ++color->r % 255;
    color->g = roundf(C*(color->r * color->r) + 255);
    color->g = clamp(color->g, 0, 255);
}

#define HYPER(SPEED) roundf((float)-(SPEED*SPEED) / 255.0f + 255.0f)

typedef struct {
    int x;
    int y;
}V2;

typedef struct {
    float x;
    float y;
}V2f;

typedef struct {
    int co;
    int begin_num;
} Formula;

void v2_switch(V2 *p1, V2 *p2){
    V2 tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

Formula derive_form(V2 ps, V2 pe)
{
    Formula form = {0};
    if(ps.x > pe.x) v2_switch(&ps, &pe);
    form.co = roundf(pe.x - ps.x / pe.y - ps.y);
    form.begin_num = (form.co * ps.x) - ps.y;
    return form;
}

void draw_bg(V2 res)
{
    for(int r = 0; r < 255; r++){
        for(int g = 0; g < 255; g++){
            int posX = r * res.x;
            int posY = g * res.y;
            DrawRectangle(posY, posX, res.x, res.y, (Color){r, 0, g ,255});
        }
    }
}

void draw_curv()
{
    for(int i = 0; i <= 255; i++){
        int y = HYPER(i);
        DrawPixel(i, y, BLACK);
    }
}

void lerp_mov_fun(const V2f *ob1, V2f *ob2, float co)
{
    if(co > 0){
        float dx = ((ob1->x - ob2->x)/co);
        float dy = ((ob1->y - ob2->y)/co);
        ob2->x += dx;
        ob2->y += dy;
    }
}

#define AC 5
void fan_mov_fun(const V2f *ob1, V2f *ob2, float co)
{
    
    float Dx = ob1->x - ob2->x;
    float Dy = ob1->y - ob2->y;
    float ax = ((Dx)/50);
    float ay = ((Dy)/50);
    ob2->x += ax * 5;
    ob2->y += ay * 5;
}

int main()
{
    //Color bg_color = {0,0,0,255};
    V2f speed = {0};
    V2f color = {100.0f, 100.0f};
    V2f color1 = {100.0f, 100.0f};
    V2f color2 = {100.0f, 100.0f};
    InitWindow(255, 400, "test");
    SetTargetFPS(20);
    while(!WindowShouldClose()){
        if(IsMouseButtonDown(0)){
            speed.x = clamp(GetMouseX(), 0, 254);
            speed.y = HYPER(speed.x);
        }
        lerp_mov_fun(&speed, &color, 25.0f);
        lerp_mov_fun(&speed, &color1, 50.0f);
        lerp_mov_fun(&speed, &color2, 75.0f);
        BeginDrawing();
            ClearBackground(BLACK);
            draw_bg((V2){1, 1});
            draw_curv();
            DrawCircle(speed.x, speed.y, 5, WHITE);
            DrawCircle(color.x, color.y, 5, BLACK);
            DrawCircle(color1.x, color1.y, 5, BLACK);
            DrawCircle(color2.x, color2.y, 5, BLACK);
            DrawRectangle(0,300,50,50,(Color){roundf(color.y), 0, roundf(color.x), 255});
            DrawRectangle(50,300,50,50,(Color){roundf(color1.y), 0, roundf(color1.x), 255});
            DrawRectangle(100,300,50,50,(Color){roundf(color2.y), 0, roundf(color2.x), 255});
        EndDrawing();
    }
    return 0;
}
