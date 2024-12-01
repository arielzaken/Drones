#pragma once

#include "Protocol/Controllers/Controller_I.h"
#include <stdint.h>

class PPPI : public Controller_I<float, float>
{
    float acc;
    float kp, ki;
public:
    PPPI(float _kp, float _ki) : acc(0), kp(_kp), ki(_ki) {}
    virtual float update(float setpoint, float measured_value) override;
};