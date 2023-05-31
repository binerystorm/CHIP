#include "./trace.h"
#define CIRC_LEN 40

CRGB data[CIRC_LEN] = {0};
void setup() { 
    FastLED.addLeds<NEOPIXEL, 6>(data, CIRC_LEN); 
}

void loop()
{
    Trace t = {
        .start = data,
        .len = 20,
        .pulse = pulse_init(data),
        .pulsing = true,
    };
    Trace t2 = {
        .start = data+20,
        .len = 20,
        .pulse = pulse_init(data+20),
        .pulsing = true,
    };

    while(t2.pulsing){
        trace_pulse(&t);
        trace_pulse(&t2);
        FastLED.show();
        delay(100);
    }
}
