#include "PPPI.h"

float PPPI::update(float setpoint, float measured_value)
{
    float error = setpoint-measured_value;
    float res = error * error * error * kp + acc * ki;
    acc = (acc + error > 100 || acc + error < -100) ? 0 : acc + error;
    return res;
}