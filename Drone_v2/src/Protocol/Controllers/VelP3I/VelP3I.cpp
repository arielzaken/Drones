#include "VelP3I.h"

inline int32_t clamp(int32_t value, int32_t min, int32_t max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

Twist<uint16_t> VelP3I::update(Velocity setpoint, Velocity measured_value)
{
    return {
        (uint16_t)clamp(xP3I.update(setpoint[X], measured_value[X]), 1000, 2000),
        (uint16_t)clamp(yP3I.update(setpoint[Y], measured_value[Y]), 1000, 2000),
        (uint16_t)clamp(zP3I.update(setpoint[Z], measured_value[Z]), 1000, 2000),
        (uint16_t)clamp(wP3I.update(setpoint[W], measured_value[W]), 1000, 2000),
    };
}