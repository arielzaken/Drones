#pragma once
#include "Operator/Behavior_I.h"
#include "Sensors/DistanceSensor/DistanceSensor.h"

class HoverBehavior : public Behavior_I
{
private:
    DistanceSensor &altSensor;
    uint16_t requiredAlt = 0;
public:
    HoverBehavior(DistanceSensor &altSensor, uint16_t reqAlt) : altSensor(altSensor), requiredAlt(reqAlt) {}
    virtual Velocity calcBehavior() override; 
    virtual void setup() override;
};