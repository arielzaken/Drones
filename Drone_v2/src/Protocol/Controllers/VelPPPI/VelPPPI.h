#pragma once

#include "Protocol/Controllers/Controller_I.h"
#include "Primitives/Primitives.h"
#include "Protocol/Controllers/PPPI/PPPI.h"
#include <stdint.h>

class VelPPPI : public Controller_I<Twist<uint16_t>, Velocity>
{
    PPPI xPPPI, yPPPI, zPPPI, wPPPI;
public:
    VelPPPI(float _kp, float _ki) :  xPPPI(_kp, _ki), yPPPI(_kp, _ki), zPPPI(_kp, _ki), wPPPI(_kp, _ki) {}
    virtual Twist<uint16_t> update(Velocity setpoint, Velocity measured_value) override;
};