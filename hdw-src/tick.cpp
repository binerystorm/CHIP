#include "tick.hpp"

bool clock_update(Clock *clk){
    clk->e_time += millis() - clk->p_time;
    if(clk->tick_len <= clk->e_time){
        clk->e_time = 0;
        clk->p_time = millis();
        return true;
    }
}

Clock clock_init(g_time_t float_tick){
    const long TICK_LEN = 100;
    return {
        0,
        0,
        TICK_LEN
    };
}
