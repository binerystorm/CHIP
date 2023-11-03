#include "control.hpp"
#include "math.hpp"

Control control_init(int stable_pin, int unstable_pin, int power_pin)
{
    Control c = {
        .state = STABLE,
        .power_state = 0,
        .state_changed = false,

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
    int st = digitalRead(c->stable_pin);
    int un = digitalRead(c->unstable_pin);
    DeviceState new_state = 
        xor_g((bool)c->state, xor_g((bool)c->state, st) &&
              xor_g(!(bool)c->state, un)) ?
                STABLE : UNSTABLE;
    c->state_changed = !(new_state == c->state);
    c->state = new_state;
    c->power_state = (float) map(analogRead(c->power_pin), 0, 1023, 0, 255);
}
