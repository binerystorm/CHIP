#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

typedef struct {
    Vector2 editor;
    
    bool layer_pickerEditMode;
    int layer_pickerActive;
    Color colors[4];
    float brightneses[4];
    int veiwActive;

    Rectangle layoutRecs[6];

} Settings;

typedef struct {
    Vector2 mode;
    
    int state_pickerActive;
    bool savePressed;
    float speedValue;

    Rectangle layoutRecs[5];

} State;

Settings InitEditor(void);
void UpdateEditor(Settings *settings);

State InitState(void);
void UpdateState(State *state);


#endif // GUI_EDITOR_H

#if defined(GUI_EDITOR_IMPLEMENTATION)

#include "raygui.h"
Settings InitEditor(void)
{
    Settings settings = { 0 };

    settings.editor = (Vector2){ 768, 48 };
    
    settings.layer_pickerEditMode = false;
    settings.layer_pickerActive = 0;
    //settings.color_pickerValue = (Color){ 0, 0, 0, 255 };
    for(int i = 0; i < 4; i++)
        settings.colors[i] = (Color){0,0,0,255};
    for(int i = 0; i < 4; i++)
        settings.brightneses[i] = 0.0f;
    settings.veiwActive = 0;

    //settings.layoutRecs[0] = (Rectangle){ 0, 0, 0, 0 };
    settings.layoutRecs[0] = (Rectangle){ settings.editor.x + 24, settings.editor.y + 16, 168, 24 };
    settings.layoutRecs[1] = (Rectangle){ settings.editor.x + 24, settings.editor.y + 96, 96, 96 };
    settings.layoutRecs[2] = (Rectangle){ settings.editor.x + 24, settings.editor.y + 208, 168, 16 };
    settings.layoutRecs[3] = (Rectangle){ settings.editor.x + 24, settings.editor.y + 56, 56, 24 };
    settings.layoutRecs[4] = (Rectangle){ settings.editor.x + 168, settings.editor.y + 96, 24, 24 };
    settings.layoutRecs[5] = (Rectangle){ 768, 56, 216, 232 };


    return settings;
}

State InitState(void)
{
    State state = {0};

    state.mode = (Vector2){ 768, 288 };

    state.savePressed = false;
    state.speedValue = 0.0f;
    state.state_pickerActive = 0;

    state.layoutRecs[0] = (Rectangle){ state.mode.x + 0, state.mode.y + 8, 216, 88 };
    state.layoutRecs[1] = (Rectangle){ state.mode.x + 24, state.mode.y + 24, 48, 24 };
    state.layoutRecs[2] = (Rectangle){ state.mode.x + 136, state.mode.y + 24, 56, 24 };
    state.layoutRecs[3] = (Rectangle){ state.mode.x + 24, state.mode.y + 64, 168, 16 };

    return state;
}
void UpdateEditor(Settings *settings)
{
    // const char *controlorText = "";
    const char *layer_pickerText = "wire;chip;glue1;glue2";
    const char *brightnessText = "";
    const char *color_pickerText = "";
    const char *veiwText = "standard;isolated;pritty";
    //const char *color_boxText = "C";
    const char *EditorText = "Editor";
    
    if (settings->layer_pickerEditMode) GuiLock();

    //GuiGroupBox(settings->layoutRecs[0], controlorText);
    GuiGroupBox(settings->layoutRecs[5], EditorText);
    GuiColorPicker(settings->layoutRecs[1], color_pickerText, &settings->colors[settings->layer_pickerActive]);
    DrawRectangleRec(settings->layoutRecs[4], settings->colors[settings->layer_pickerActive]);
    GuiSlider(settings->layoutRecs[2], brightnessText, NULL, &settings->brightneses[settings->layer_pickerActive], 0, 255);
    GuiToggleGroup(settings->layoutRecs[3], veiwText, &settings->veiwActive);
    if (GuiDropdownBox(settings->layoutRecs[0], layer_pickerText, &settings->layer_pickerActive, settings->layer_pickerEditMode)) settings->layer_pickerEditMode = !settings->layer_pickerEditMode;
    
    GuiUnlock();
}

void UpdateState(State *state)
{
    const char *state_boxText = "State Select";
    const char *state_pickerText = "Stable;Faulty";
    const char *saveText = "SAVE";
    const char *speedText = "";

    GuiGroupBox(state->layoutRecs[0], state_boxText);
    GuiToggleGroup(state->layoutRecs[1], state_pickerText, &state->state_pickerActive);
    state->savePressed = GuiButton(state->layoutRecs[2], saveText); 
    GuiSlider(state->layoutRecs[3], speedText, NULL, &state->speedValue, 0, 100);
}

#endif // GUI_EDITOR_IMPLEMENTATION
