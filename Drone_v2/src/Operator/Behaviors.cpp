#include "Behaviors.h"
#include <esp32-hal-timer.h>
Velocity TakeoffBehavior::calcBehavior()
{ 
    int32_t height = sensor->read();
    if(height < 20)
        oldTwist[Z] = ((millis() - startTime) / 1000);
    return oldTwist;
}

void TakeoffBehavior::setup()
{
    startTime = millis();
}

Velocity LandBehavior::calcBehavior()
{
    return {0,0,-1, 0};
}

void LandBehavior::setup()
{
}

Velocity TransitBehavior::calcBehavior()
{
    return Velocity();
}

void TransitBehavior::setup()
{
}

Velocity CollisionAvoidanceBehavior::calcBehavior()
{
    return {1,2,3,0};
}

void CollisionAvoidanceBehavior::setup()
{
}
