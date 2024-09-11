#pragma once
#include "Operator/Operator/Operator.h"
class State_I{
public:
    virtual void handle(Operator* this_) = 0;
};

class GroundState : public State_I{
    virtual void handle(Operator* this_);
};

class CheckState : public State_I{
    virtual void handle(Operator* this_);
};

class TakeoffState : public State_I{
    virtual void handle(Operator* this_);
};

class TransitState : public State_I{
    virtual void handle(Operator* this_);
};

class LandState : public State_I{
    virtual void handle(Operator* this_);
};