#include "OperatorTypes.h"
class Behavior_I
{
    virtual Twist calcBehavior(Twist twist) = 0;
};