#include <Arduino.h>

#ifndef _CONTROL_H_
#define _CONTROL_H_

typedef enum {
    UNSTABLE = 0,
    STABLE
} DeviceState;

typedef struct {
    DeviceState state;
    float power_state;

    const int stable_pin;
    const int unstable_pin;
    const int power_pin;
} Control;

Control control_init(int stable_pin, int unstabel_pin, int power_pin);
void control_update(Control *c);

#endif // _CONTROL_H_
