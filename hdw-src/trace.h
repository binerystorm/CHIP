#include <Arduino.h>
//#include <cstddef>
#include <FastLED.h>


#define on_state CRGB::Red
#define off_state CRGB::Black
//#define on_state true
//#define off_state false
#define PULSE_LEN 6 // Exclusive end

// typedef bool Type;
typedef CRGB Type;

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

Pulse pulse_init(Type *loc);
void circuit_init(Trace *traces, const size_t *lens, const size_t n, Type *data);
void trace_pulse(Trace *trace);
