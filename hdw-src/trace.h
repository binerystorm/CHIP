#include <math.h>

#ifdef SIMULATION
    #include <stdlib.h>
    #include <stdbool.h>
    #define on_state true
    #define off_state false
    typedef bool Type;

#else
    #include <Arduino.h>
    #include <FastLED.h>
    #define on_state CRGB::Red
    #define off_state CRGB::Black
    typedef CRGB Type;
#endif


#define PULSE_LEN 6 // Exclusive end


typedef struct {
    Type *start;
    Type *end;
    size_t len;
} Pulse;

typedef struct {
    Type *start;
    Type *end;
    //size_t len;
    Pulse pulse;
    bool pulsing;
} Trace;

Pulse pulse_init(Type *loc, const size_t len);
void circuit_init(Trace *traces, const size_t *lens, const size_t n, Type *data);
void trace_pulse(Trace *trace);
