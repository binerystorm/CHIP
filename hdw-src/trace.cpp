#include "./trace.h"
Pulse pulse_init(Type *loc, const size_t len){
    return (Pulse) {
        .start = loc,
        .end = loc,
        .len = len,
    };
}

void circuit_init(Trace *traces, const size_t *lens, const size_t n, Type *data)
{
    Type *cur = data;
    for(size_t i = 0; i < n; i++)
    {
        size_t current_len = lens[i];
        traces[i] = {
            .start = cur,
            .end = cur + current_len,
            .pulse = pulse_init(cur, (current_len > PULSE_LEN) ? PULSE_LEN : current_len),
            .pulsing = true,
        };
        cur += current_len;
    }
}

void trace_pulse(Trace *trace)
{
    Pulse *pulse = &(trace->pulse);

    if((pulse->start > trace->end)){
        trace->pulsing = false;
        pulse->start = trace->start;
        pulse->end = trace->start;
        return;
    }
    if(pulse->end < trace->end){
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
