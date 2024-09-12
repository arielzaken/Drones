#pragma once
#include "Operator/Behavior_I.h"
class TakeoffBehavior : public Behavior_I
{
public:
    virtual Twist calcBehavior(Twist twist) override;
};

class LandBehavior : public Behavior_I
{
public:
    virtual Twist calcBehavior(Twist twist) override;
};

class TransitBehavior : public Behavior_I
{
public:
    virtual Twist calcBehavior(Twist twist) override;
};

class CollisionAvoidanceBehavior : public Behavior_I
{
public:
    virtual Twist calcBehavior(Twist twist) override;
};