#include "tick.h"

//bool clock_update(Clock *clk){
//    clk->e_time += millis() - clk->p_time;
//    clk->p_time = millis();
//    if(clk->tick_len <= clk->e_time){
//        clk->e_time = 0;
//        return true;
//    }
//}
bool clock_update(Clock *clk){
    clk->e_time += GetFrameTime();
    clk->p_time = GetTime();
    if(clk->tick_len <= clk->e_time){
        clk->e_time = 0;
        return true;
    }
    return false;
}

Clock clock_init(g_time_t float_tick){
    //const float TICK_LEN = 0.1f;
    const long TICK_LEN = 1;
    return (Clock) {
        .e_time = 0,
        .p_time = 0,
        .tick_len = TICK_LEN
    };
}
