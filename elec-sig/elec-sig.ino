#include "./trace.h"
#define CIRC_LEN 40
#define TRACE_COUNT 3

CRGB data[CIRC_LEN] = {0};
Trace circuit[TRACE_COUNT] = {0};
const size_t trace_lens[TRACE_COUNT] = {20, 3, 7};

void setup() { 
    FastLED.addLeds<NEOPIXEL, 6>(data, CIRC_LEN); 
    circuit_init(circuit, trace_lens, TRACE_COUNT, data);
}

void loop()
{
    for(auto &t : circuit){
        trace_pulse(&t);
    }
    FastLED.show();
    delay(100);
}
