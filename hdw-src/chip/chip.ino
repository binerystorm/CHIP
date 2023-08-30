#include <FastLED.h>
#include "chip.hpp"
#include "tick.hpp"
Type data[DATACAP] = {0};
int coef = 1;
//V2f speed = {0};
float speed = 0.0f;
size_t caps[4] = {CHIPCAP, GLUE1CAP, WIRECAP, GLUE2CAP};
//GuiChipStruct chip_struct = InitGuiChip();
//State state = InitState();
Chip chip = {0};
Clock clk = clock_init(0.4f);
size_t tick_counter = 0;
bool frame_updated = false;

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

void setup() {
    FastLED.addLeds<NEOPIXEL, 6>(data, DATACAP);
    pinMode(A1, INPUT);
    chip_init(&chip, caps, data, DATACAP);
}


void loop() {
    //chip_animate(&chip, tick_counter);
    FastLED.show();
    {
        //speed.x = (float) map(analogRead(A1), 0, 1000, 0, 255);
        //speed.y = roundf(HYPER(speed.x, coef));
        speed = (float) map(analogRead(A1), 0, 1000, 0, 255);
    }
    if(clock_update(&clk)) tick_counter += 1;
    if(tick_counter % 3 == 0) frame_updated = false;
    if(!frame_updated){
        //sec_lerp_update(&speed, &chip.chip, 100);
        //sec_fill(&chip.chip);
        //sec_lerp_update(&speed, &chip.glue1, 75);
        //sec_fill(&chip.glue1);
        //sec_lerp_update(&speed, &chip.glue2, 35);
        //sec_fill(&chip.glue2);
        sec_lerp_update_1d(&speed, &chip.chip, 900);
        sec_fill_gradient(&chip.chip);
        sec_lerp_update_1d(&speed, &chip.glue1, 675);
        sec_fill_gradient(&chip.glue1);
        sec_lerp_update_1d(&speed, &chip.glue2, 315);
        sec_fill_gradient(&chip.glue2);
        frame_updated = true;
    }
    //else coef = 5;
    //delay(100);
}
