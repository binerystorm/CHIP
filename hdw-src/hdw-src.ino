#include "chip.hpp"
#include "trace.h"
#include "control.hpp"
#include "tick.hpp"

#define TRACE_COUNT 20
#define TRACE_DATACAP 120

Type data[CHIP_DATACAP + TRACE_DATACAP] = {0};
size_t caps[4] = {CHIPCAP, GLUE1CAP, WIRECAP, GLUE2CAP};
const size_t trace_lens[TRACE_COUNT] = {5,6,4,6,4,5,4,7,6,12,4,5,9,5,4,8,3,3,8,12};
Trace circuit[TRACE_COUNT] = {0};

int coef = 1;
Chip chip = {0};
Control control = control_init(5, 4, A1);
Clock clk = clock_init(0.4f);
size_t tick_counter = 0;
bool chip_frame_updated = false;
bool circuit_frame_updated = false;
uint8_t count = 0;

void setup()
{
    FastLED.addLeds<NEOPIXEL, 6>(data, CHIP_DATACAP + TRACE_DATACAP);
    Serial.begin(9600);
    pinMode(A1, INPUT);
    chip_init(&chip, caps, data + TRACE_DATACAP, CHIP_DATACAP);
    circuit_init(circuit, trace_lens, TRACE_COUNT, data);

}
void loop()
{

    control_update(&control);
    if(clock_update(&clk)){
        tick_counter += 1;
        FastLED.show();
        int16_t heat = clamp(map(control.power_state, 0, 255, 255, 0),
                             0, 255 - (control.state * 125));

        sec_fill_gradient(&chip.chip);
        sec_fill_gradient(&chip.glue1);
        sec_fill_gradient(&chip.glue2);
        sec_fill_color(&chip.wire, CRGB::Yellow)
        sec_range_fill_color(&chip.wire, 4, 6, CRGB::Black);

        if(tick_counter % 3 == 0){
            sec_lerp_update(heat, &chip.chip, 700.0f);
            sec_lerp_update(heat, &chip.glue1, 475.0f);
            sec_lerp_update(heat, &chip.glue2, 115.0f);
        }
        if(tick_counter % 10 == 0){
            for(auto &t : circuit){
                if(t.pulsing){
                    trace_pulse(&t, control.state ? CRGB::Blue : CRGB::Red);
                    if (!t.pulsing) count--;
                }else{
                    if(count <= 10 && random((int)round(control.power_state)) == 0){
                        t.pulsing = true;
                        count++;
                    }
                }
            }
        }
    } 
}
