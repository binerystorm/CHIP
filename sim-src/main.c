#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <raylib.h>
#include <math.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
// #define GUI_LAYOUT_NAME_IMPLEMENTATION
// #include "edit_module.h"
#define GUI_EDITOR_IMPLEMENTATION
#include "editor.h"
#define GUI_CHIP_IMPLEMENTATION
#include "chip_struct.h"

#include "chip.h"
#include "tick.h"

#define V2Unpack(V2) V2.x, V2.y


Vector2 rectangle_center(Rectangle rec)
{
    return (Vector2) {
        rec.x + rec.width,
        rec.y + rec.height
    };
}

void chip_full_render(const Type *data, 
                 const Rectangle *structr)
{
    for(int i = 0; i < DATACAP; i++){
        Color c1 = data[i];
        //c1.a = settings->brightnessValue;
        Color c2 = data[i];
        c2.a = 0;
        DrawCircleGradient(V2Unpack(rectangle_center(structr[i])), 30, c1, c2);
    }
}

void save(const Color *color, const char *names, size_t n, const char *file)
{
    FILE *f = fopen(file, "w");
    
    for(int i = 0; i < n; i++) {
        Color c = color[i];
        char data[50] = {0};
        const char* str = &(names[i*7]);
        const size_t n = snprintf(data,
                                  50,
                                  "%s: {%d,%d,%d,%d}\n",
                                  str,
                                  c.r, c.g, c.b, c.a);
        //snprintf(data, n, "%s: {%d,%d,%d,%d}\n", names[i], c.r, c.g, c.b, c.a);
        fwrite(data, 1, n, f);
    }
    fclose(f);
}

bool color_cmp(Type *color1, Type color2){
    if(color1->r != color2.r) return true;
    if(color1->g != color2.g) return true;
    if(color1->b != color2.b) return true;
    return false;
}

void flicker(Chip *chip){
    if(chip->glue1.on){
        chip->glue2.on = true;
        chip->glue1.on = false;
    }else{
        chip->glue2.on = false;
        chip->glue1.on = true;
    }

    if(chip->glue2.on)
        sec_fill(&chip->glue2);
    else
        sec_clear(&chip->glue2);
    if(chip->glue1.on)
        sec_fill(&chip->glue1);
    else
        sec_clear(&chip->glue1);
}

void chip_animate(Chip *chip, const size_t tick_counter){
    const size_t frame = tick_counter % 8;
    if (frame > 3){
        sec_fill(&chip->glue2);
    }
    if (frame > 5){
        sec_fill(&chip->glue1);
    }
    if (frame <= 3){
        sec_clear(&chip->glue1);
        sec_clear(&chip->glue2);
    }
}

int main()
{
    assert((CHIPCAP + WIRECAP + GLUE1CAP + GLUE2CAP) == DATACAP && "values incorrect");

    int coef = 1;
    //V2f speed = {0};
    float speed = 0.0f;
    Type data[DATACAP] = {0};
    size_t caps[4] = {CHIPCAP, WIRECAP, GLUE1CAP, GLUE2CAP};
    GuiChipStruct chip_struct = InitGuiChip();
    State state = InitState();
    Chip chip = {0};
    Clock clk = clock_init(0.4f);
    size_t tick_counter = 0;

    chip_init(&chip, caps, data, DATACAP);
    InitWindow(1000,500, "Chip");
    SetTargetFPS(20);
    while(!WindowShouldClose()){
        BeginDrawing();{
            ClearBackground(RAYWHITE);
            chip_full_render(data, chip_struct.layoutRecs);
        }EndDrawing();
        {
            //speed.x = (float) state.speedValue;
            //speed.y = roundf(HYPER(speed.x, coef));
            speed = (float) state.speedValue;
        }
        if (tick_counter % 3 == 0){
            sec_lerp_update_1d(&speed, &chip.chip, 100);
            sec_fill_gradient(&chip.chip);
            sec_lerp_update_1d(&speed, &chip.glue1, 75);
            sec_fill_gradient(&chip.glue1);
            sec_lerp_update_1d(&speed, &chip.glue2, 35);
            sec_fill_gradient(&chip.glue2);
        }
        if(state.state_pickerActive == 1) coef = 1;
        else coef = 5;
        if(clock_update(&clk)) tick_counter += 1;
        UpdateState(&state);
    }
    return 0;
}
