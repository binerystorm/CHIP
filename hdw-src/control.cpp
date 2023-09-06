#include "control.hpp"

Control control_init(int stable_pin, int unstable_pin, int power_pin)
{
    Control c = {
        .stable_state = true,
        .unstable_state = false,
        .power_state = 0,

        .stable_pin = stable_pin,
        .unstable_pin = unstable_pin,
        .power_pin = power_pin,
    };
    pinMode(stable_pin, INPUT);
    pinMode(unstable_pin, INPUT);
    pinMode(power_pin, INPUT);
    return c;
}

void control_update(Control *c)
{
    bool st = digitalRead(c->stable_pin);
    bool un = digitalRead(c->unstable_pin);
    if(st){
        c->stable_state = true;
        c->unstable_state = false;
    }
    if(un){
        c->stable_state = false;
        c->unstable_state = true;
    }
    c->power_state = (float) map(analogRead(c->power_pin), 0, 1000, 0, 255);
}
