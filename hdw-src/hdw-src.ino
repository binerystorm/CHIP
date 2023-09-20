#include "chip.hpp"
#include "trace.h"
#include "control.hpp"
#include "tick.hpp"

#define TRACE_COUNT 20
#define TRACE_DATACAP 120

Type data[DATACAP + TRACE_DATACAP] = {0};
size_t caps[4] = {CHIPCAP, GLUE1CAP, WIRECAP, GLUE2CAP};
const size_t trace_lens[TRACE_COUNT] = {5,6,4,6,4,5,4,7,6,12,4,5,9,5,4,8,3,3,8,12};
Trace circuit[TRACE_COUNT] = {0};

int coef = 1;
Chip chip = {0};
Control control = control_init(3, 4, A1);
Clock clk = clock_init(0.4f);
size_t tick_counter = 0;
bool chip_frame_updated = false;
bool circuit_frame_updated = false;
uint8_t count = 0;
// Trace chip_trace = {0};

void setup()
{
    FastLED.addLeds<NEOPIXEL, 6>(data, DATACAP + TRACE_DATACAP);
    Serial.begin(9600);
    pinMode(A1, INPUT);
    chip_init(&chip, caps, data + TRACE_DATACAP, DATACAP);
    circuit_init(circuit, trace_lens, TRACE_COUNT, data);

}

void loop()
{

    control_update(&control);
    if(clock_update(&clk)){
        FastLED.show();
        tick_counter += 1;

        if(tick_counter % 3 == 0){
            sec_lerp_update_1d(&(control.power_state), &chip.chip, 900);
            sec_fill_gradient(&chip.chip);
            sec_lerp_update_1d(&(control.power_state), &chip.glue1, 675);
            sec_fill_gradient(&chip.glue1);
            sec_lerp_update_1d(&(control.power_state), &chip.glue2, 315);
            sec_fill_gradient(&chip.glue2);
            sec_lerp_update(&((V2f){255,0}), &chip.wire, 315);
            sec_fill(&(chip.wire));
        }
        if(tick_counter % 10 == 0){
            Serial.println(control.power_state);
            
            for(auto &t : circuit){
                if(t.pulsing){
                    trace_pulse(&t);
                    if (!t.pulsing) count--;
                }else{
                    if(count <= 5 && random((int)round(control.power_state)) == 0){
                        t.pulsing = true;
                        count++;
                    }
                }
            }
        }
    } 
    // if(tick_counter % 10 == 0){
    //     if(chip_trace.pulsing)
    //         trace_pulse(&chip_trace);
    //     else{
    //         if(random(map((int)control.power_state, 0,255, 25,0)) == 0) chip_trace.pulsing = true;
    //     }
    // }
}
