#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
// #define GUI_LAYOUT_NAME_IMPLEMENTATION
// #include "edit_module.h"
#define GUI_EDITOR_IMPLEMENTATION
#include "editor.h"
#define GUI_CHIP_IMPLEMENTATION
#include "chip.h"

#define DATACAP 37
#define CHIPCAP 6
#define WIRECAP 15
#define GLUE1CAP 6
#define GLUE2CAP 10

#define GLUE1START 0
#define WIRESTART GLUE1CAP
#define CHIPSTART WIRECAP+GLUE1CAP
#define GLUE2START WIRECAP+GLUE1CAP+CHIPCAP

#define V2Unpack(V2) V2.x, V2.y

typedef Color Type;

typedef struct {
} Section;

typedef struct {
    Type *glue1; // green
    Type *wire;   // red
    Type *chip;   // blue
    Type *glue2; // pink
} Chip;

Vector2 rectangle_center(Rectangle rec)
{
    return (Vector2) {
        rec.x + rec.width,
        rec.y + rec.height
    };
}

void fill_colors(Chip *chip)
{
    size_t cur = 0;
    for(size_t loc_cur = 0; loc_cur < GLUE1CAP; loc_cur++)
        chip->glue1[loc_cur] = GREEN;
    for(size_t loc_cur = 0; loc_cur < WIRECAP; loc_cur++)
        chip->wire[loc_cur] = RED;
    for(size_t loc_cur = 0; loc_cur < CHIPCAP; loc_cur++)
        chip->chip[loc_cur] = BLUE;
    for(size_t loc_cur = 0; loc_cur < GLUE2CAP; loc_cur++)
        chip->glue2[loc_cur] = PINK;
}

void chip_update_color(Chip *chip, Settings *settings)
{
    switch(settings->layer_pickerActive){
        case 0:{
            for(int i = 0; i < WIRECAP; i++){
                chip->wire[i] = settings->colors[settings->layer_pickerActive];
                chip->wire[i].a = settings->brightneses[settings->layer_pickerActive];
            }
        } break;
        case 1:{
            for(int i = 0; i < CHIPCAP; i++){
                chip->chip[i] = settings->colors[settings->layer_pickerActive];
                chip->chip[i].a = settings->brightneses[settings->layer_pickerActive];

            }
        } break;
        case 2:{
            for(int i = 0; i < GLUE1CAP; i++){
                chip->glue1[i] = settings->colors[settings->layer_pickerActive];
                chip->glue1[i].a = settings->brightneses[settings->layer_pickerActive];
            }
        } break;
        case 3:{
            for(int i = 0; i < GLUE2CAP; i++){
                chip->glue2[i] = settings->colors[settings->layer_pickerActive];
                chip->glue2[i].a = settings->brightneses[settings->layer_pickerActive];
            }
        } break;
    }
}

void chip_render(const Type *data, 
                 const Rectangle *structr, 
                 const Settings *settings)
{
    if(settings->veiwActive == 0){
        for(int i = 0; i < DATACAP; i++){
            Color c1 = data[i];
            //c1.a = settings->brightnessValue;
            Color c2 = data[i];
            c2.a = 0;
            DrawCircleGradient(V2Unpack(rectangle_center(structr[i])), 30, c1, c2);
        }
    } else if(settings->veiwActive == 1){
        switch(settings->layer_pickerActive){
            case 0:{
                for(int i = WIRESTART; i < WIRESTART+WIRECAP; i++){
                    Color c1 = data[i];
                    Color c2 = data[i];
                    c2.a = 0;
                    DrawCircleGradient(V2Unpack(rectangle_center(structr[i])), 30, c1, c2);
                }

            }break;
            case 1:{
                for(int i = CHIPSTART; i < CHIPSTART+CHIPCAP; i++){
                    Color c1 = data[i];
                    Color c2 = data[i];
                    c2.a = 0;
                    DrawCircleGradient(V2Unpack(rectangle_center(structr[i])), 30, c1, c2);
                }
            }break;
            case 2:{
                for(int i = GLUE1START; i < GLUE1START+GLUE1CAP; i++){
                    Color c1 = data[i];
                    Color c2 = data[i];
                    c2.a = 0;
                    DrawCircleGradient(V2Unpack(rectangle_center(structr[i])), 30, c1, c2);
                }
            }break;
            case 3:{
                for(int i = GLUE2START; i < GLUE2START+GLUE2CAP; i++){
                    Color c1 = data[i];
                    Color c2 = data[i];
                    c2.a = 0;
                    DrawCircleGradient(V2Unpack(rectangle_center(structr[i])), 30, c1, c2);
                }
            }break;
        }
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

int main()
{
    assert((CHIPCAP + WIRECAP + GLUE1CAP + GLUE2CAP) == DATACAP && "values incorrect");

    Type data[DATACAP] = {0};
    Chip chip = (Chip){
        .glue1 = data,
        .wire = data + WIRESTART,
        .chip = data + CHIPSTART,
        .glue2 = data + GLUE2START
    };
    GuiChipStruct chip_struct = InitGuiChip();

    //fill_colors(&chip);
    Settings settings = InitEditor();
    State state = InitState();
    Color current_color = {0};
    current_color.a = 255;

    InitWindow(1000,500, "Chip");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        chip_update_color(
                &chip,
                &settings
            );
        //GuiEditModule(&state);
        UpdateEditor(&settings);
        UpdateState(&state);
        chip_render(data, chip_struct.layoutRecs, &settings);
        if(state.savePressed){
            Color arr[4] = {chip.wire[0], chip.chip[0], chip.glue1[0], chip.glue2[0]};
            const char names[] = "wire  \0chip  \0glue1 \0glue2 ";
            save(arr, names, 4, "color.txt");
        }
        EndDrawing();
    }
    return 0;
}
