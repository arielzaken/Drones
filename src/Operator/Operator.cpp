#include "Operator.h"

Operator OP;

uint16_t Operator::mapAltToThrottle(ALTITUDE_DATA alt)
{
    return controller.getThrottle() + (alt.EstAlt);
}

void Operator::begin()
{
    controller.begin();
    delay(10000);
    controller.arm();
    controller.loop();
}

void Operator::loop()
{
    /*ALTITUDE_DATA alt = controller.getAltitude();
    if(alt.EstAlt >= MAX_ALT)
        emergencyLanding();*/
    controller.loop();
}

void Operator::takeOff()
{
    state = TAKE_OFF;
    //TODO: the thing
}

void Operator::emergencyLanding()
{
    state = EMERGENCY_LANDING;
    controller.disconnect();
}
