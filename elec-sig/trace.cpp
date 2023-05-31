#include "./trace.h"
Pulse pulse_init(Type *loc){
    return (Pulse) {
        .start = loc,
        .end = loc,
        .len = PULSE_LEN,
    };
}

void trace_pulse(Trace *trace)
{
    //Pulse pulse = {
    //    .start = wire,
    //    .end = wire,
    //    .len = PULSE_LEN,
    //};
    Pulse *pulse = &(trace->pulse);

    if(!(pulse->start < trace->start + trace->len)){
        trace->pulsing = false;
        pulse->start = trace->start;
        pulse->end = trace->start;
        return;
    }
    if(pulse->end < trace->start + trace->len){
        *(pulse->end) = on_state;
        (pulse->end)++;
    }
    if(pulse->end - pulse->start >= pulse->len){
        // assert((pulse->end - pulse->start) == pulse->len);
        *(pulse->start) = off_state;
        (pulse->start)++;
    }else if(pulse->start > trace->start){
        *(pulse->start) = off_state;
        (pulse->start)++;
    }
    
}
