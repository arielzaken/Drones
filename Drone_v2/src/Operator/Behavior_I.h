#pragma once
#include "OperatorTypes.h"
class Behavior_I
{
public:
    virtual Twist calcBehavior() = 0;
    virtual void setup() = 0;
};