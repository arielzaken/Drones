#pragma once
#include "Operator/Behavior_I.h"
class TakeoffBehavior : public Behavior_I
{
public:
    virtual Twist calcBehavior(Twist twist);
};

class LandBehavior : public Behavior_I
{
public:
    virtual Twist calcBehavior(Twist twist);
};

class TransitBehavior : public Behavior_I
{
public:
    virtual Twist calcBehavior(Twist twist);
};

class CollisionAvoidanceBehavior : public Behavior_I
{
public:
    virtual Twist calcBehavior(Twist twist);
};