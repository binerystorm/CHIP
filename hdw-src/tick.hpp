#include <Arduino.h>
typedef long g_time_t;

typedef struct{
    g_time_t p_time;
    g_time_t e_time;
    const g_time_t tick_len;
} Clock;

Clock clock_init(g_time_t float_tick);
bool clock_update(Clock *clk);
