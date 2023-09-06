#include "./trace.h"
#define CIRC_LEN 40
#define TRACE_COUNT 8

CRGB data[CIRC_LEN] = {0};
Trace circuit[TRACE_COUNT] = {0};
const size_t trace_lens[TRACE_COUNT] = {5, 5, 5, 5, 5, 5, 5, 5};
long speed;

void setup() { 
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, 6>(data, CIRC_LEN); 
    circuit_init(circuit, trace_lens, TRACE_COUNT, data);
    pinMode(A1, INPUT);
}

void loop()
{
    speed = map(analogRead(A1), 0, 600, 75, 0);
    Serial.println(speed);
    Serial.println(analogRead(A1));
    for(auto &t : circuit){
        if(t.pulsing)
            trace_pulse(&t);
        else{
            if(random(speed) == 0) t.pulsing = true;
        }
    }
    FastLED.show();
    delay(50);
}
