#include "chip.hpp"
#include "trace.h"
#include "control.hpp"
#include "tick.hpp"

Type data[DATACAP] = {0};
size_t caps[4] = {CHIPCAP, GLUE1CAP, WIRECAP, GLUE2CAP};

int coef = 1;
Chip chip = {0};
Control control = control_init(3, 4, A1);
Clock clk = clock_init(0.4f);
size_t tick_counter = 0;
bool frame_updated = false;
// Trace chip_trace = {0};

void setup()
{
    FastLED.addLeds<NEOPIXEL, 6>(data, DATACAP);
    pinMode(A1, INPUT);
    chip_init(&chip, caps, data, DATACAP);
    // circuit_init(&chip_trace, {WIRECAP}, 1, chip.wire.data);

}

void loop()
{
    control_update(&control);
    FastLED.show();
    if(clock_update(&clk)) tick_counter += 1;
    if(tick_counter % 3 == 0) frame_updated = false;
    if(!frame_updated){
        sec_lerp_update_1d(&(control.power_state), &chip.chip, 900);
        sec_fill_gradient(&chip.chip);
        sec_lerp_update_1d(&(control.power_state), &chip.glue1, 675);
        sec_fill_gradient(&chip.glue1);
        sec_lerp_update_1d(&(control.power_state), &chip.glue2, 315);
        sec_fill_gradient(&chip.glue2);
        sec_lerp_update(&((V2f){255,0}), &chip.wire, 315);
        sec_fill(&(chip.wire));
        frame_updated = true;
    }
    // if(tick_counter % 10 == 0){
    //     if(chip_trace.pulsing)
    //         trace_pulse(&chip_trace);
    //     else{
    //         if(random(map((int)control.power_state, 0,255, 25,0)) == 0) chip_trace.pulsing = true;
    //     }
    // }
}
