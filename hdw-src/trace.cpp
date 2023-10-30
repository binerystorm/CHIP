#include "./trace.h"
Pulse pulse_init(Type *loc, const size_t len){
    return (Pulse) {
        .start = loc - len,
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

void trace_pulse(Trace *trace, Type on_state)
{
    Pulse *pulse = &(trace->pulse);

    // prohibit setting of state outside of trace region
    if(pulse->start >= trace->start)
        *(pulse->start) = off_state;
    if(pulse->end < trace->end)
        *(pulse->end) = on_state;

    (pulse->end)++;
    (pulse->start)++;

    // reset for next round
    if(pulse->start >= trace->end){
        trace->pulsing = false;
        pulse->start = trace->start - pulse->len;
        pulse->end = trace->start;
        return;
    }

}
