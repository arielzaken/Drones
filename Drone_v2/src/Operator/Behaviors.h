#pragma once
#include "Operator/Behavior_I.h"
#include "Sensors/DistanceSensor/DistanceSensor.h"
class TakeoffBehavior : public Behavior_I
{
    unsigned long startTime;
    DistanceSensor *sensor;
    Twist oldTwist;
public:
    TakeoffBehavior(DistanceSensor &sensor) : sensor(&sensor){}
    virtual Twist calcBehavior() override;
    virtual void setup() override;
};

class LandBehavior : public Behavior_I
{
public:
    virtual Twist calcBehavior() override;
    virtual void setup() override;
};

class TransitBehavior : public Behavior_I
{
public:
    virtual Twist calcBehavior() override;
    virtual void setup() override;
};

class CollisionAvoidanceBehavior : public Behavior_I
{
public:
    virtual Twist calcBehavior() override; 
    virtual void setup() override;
};