#include "Behaviors.h"
#include <esp32-hal-timer.h>
Twist TakeoffBehavior::calcBehavior()
{ 
    int32_t height = sensor->read();
    if(height < 20)
        oldTwist.v.z = ((millis() - startTime) / 1000);

    return oldTwist;
}

void TakeoffBehavior::setup()
{
    startTime = millis();
}

Twist LandBehavior::calcBehavior()
{
    return Twist(vec3D(0,0,-1), 0);
}

void LandBehavior::setup()
{
}

Twist TransitBehavior::calcBehavior()
{
    return Twist();
}

void TransitBehavior::setup()
{
}

Twist CollisionAvoidanceBehavior::calcBehavior()
{
    return Twist(vec3D(1, 2, 3), 0);
}

void CollisionAvoidanceBehavior::setup()
{
}
