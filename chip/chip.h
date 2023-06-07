#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()
#include <stdlib.h>

#ifndef GUI_CHIP_H
#define GUI_CHIP_H

typedef struct {
    Rectangle layoutRecs[38];
} GuiChipStruct;

GuiChipStruct InitGuiChip();
void GuiChip(Rectangle *recs, Color *colors, size_t len);

#endif // GUI_CHIP_H

#if defined(GUI_CHIP_IMPLEMENTATION)

#include "raygui.h"

GuiChipStruct InitGuiChip()
{
    GuiChipStruct structure = { 0 };
    
    // order of array: g:r:b:p
    structure.layoutRecs[0] = (Rectangle){ 120, 72, 24, 24 };
    structure.layoutRecs[1] = (Rectangle){ 120, 200, 24, 24 };
    structure.layoutRecs[2] = (Rectangle){ 120, 328, 24, 24 };
    structure.layoutRecs[3] = (Rectangle){ 456, 72, 24, 24 };
    structure.layoutRecs[4] = (Rectangle){ 456, 200, 24, 24 };
    structure.layoutRecs[5] = (Rectangle){ 456, 328, 24, 24 };
    structure.layoutRecs[6] = (Rectangle){ 120, 104, 24, 24 };
    structure.layoutRecs[7] = (Rectangle){ 120, 40, 24, 24 };
    structure.layoutRecs[8] = (Rectangle){ 120, 168, 24, 24 };
    structure.layoutRecs[9] = (Rectangle){ 120, 232, 24, 24 };
    structure.layoutRecs[10] = (Rectangle){ 120, 296, 24, 24 };
    structure.layoutRecs[11] = (Rectangle){ 120, 360, 24, 24 };
    structure.layoutRecs[12] = (Rectangle){ 288, 384, 24, 24 };
    structure.layoutRecs[13] = (Rectangle){ 256, 40, 24, 24 };
    structure.layoutRecs[14] = (Rectangle){ 320, 40, 24, 24 };
    structure.layoutRecs[15] = (Rectangle){ 456, 40, 24, 24 };
    structure.layoutRecs[16] = (Rectangle){ 456, 104, 24, 24 };
    structure.layoutRecs[17] = (Rectangle){ 456, 168, 24, 24 };
    structure.layoutRecs[18] = (Rectangle){ 456, 232, 24, 24 };
    structure.layoutRecs[19] = (Rectangle){ 456, 296, 24, 24 };
    structure.layoutRecs[20] = (Rectangle){ 456, 360, 24, 24 };
    structure.layoutRecs[21] = (Rectangle){ 152, 72, 24, 24 };
    structure.layoutRecs[22] = (Rectangle){ 152, 200, 24, 24 };
    structure.layoutRecs[23] = (Rectangle){ 152, 328, 24, 24 };
    structure.layoutRecs[24] = (Rectangle){ 424, 72, 24, 24 };
    structure.layoutRecs[25] = (Rectangle){ 424, 200, 24, 24 };
    structure.layoutRecs[26] = (Rectangle){ 424, 328, 24, 24 };
    structure.layoutRecs[27] = (Rectangle){ 88, 72, 24, 24 };
    structure.layoutRecs[28] = (Rectangle){ 88, 136, 24, 24 };
    structure.layoutRecs[29] = (Rectangle){ 88, 200, 24, 24 };
    structure.layoutRecs[30] = (Rectangle){ 88, 264, 24, 24 };
    structure.layoutRecs[31] = (Rectangle){ 88, 328, 24, 24 };
    structure.layoutRecs[32] = (Rectangle){ 488, 72, 24, 24 };
    structure.layoutRecs[33] = (Rectangle){ 488, 136, 24, 24 };
    structure.layoutRecs[34] = (Rectangle){ 488, 200, 24, 24 };
    structure.layoutRecs[35] = (Rectangle){ 488, 264, 24, 24 };
    structure.layoutRecs[36] = (Rectangle){ 488, 328, 24, 24 };

    return structure;
}

void GuiChip(Rectangle *recs, Color *colors, size_t len)
{
    for(int i = 0; i < len; i++)
    {
            DrawRectangleRec(recs[i], colors[i]);
    }
}

#endif // GUI_CHIP_IMPLEMENTATION
