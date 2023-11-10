#include "Operator.h"

Operator OP;

uint16_t Operator::mapAltToThrottle(ALTITUDE_DATA alt)
{
    return controller.getThrottle() + (alt.EstAlt);
}

void Operator::arm(uint64_t time)
{   
    if(time<=200)
        controller.disarm();
    else if(time>=5000)
        controller.arm();
    else{
        state = IDLE_GROUND;
    }
}

/// @brief this func init the operator. (without delay to avoid BAD-RX-timeout)
void Operator::begin()
{
    controller.begin();
}

void Operator::loop()
{
    switch(state){
    case ARM:
        arm(PP.getTime());
        break;
    case TAKE_OFF:
        takeOff(PP.getTime());
        break;
    case IDLE_AIR:
        PP.reset();
        break;
    case IDLE_GROUND:
        PP.reset();
        break;
    case EMERGENCY_LANDING:
        break;
    }



    // check if we exceeded the limit of the highet
    ALTITUDE_DATA alt = controller.getAltitude();
    if(alt.EstAlt >= MAX_ALT)
        emergencyLanding();
    
    controller.loop();
}

void Operator::arm()
{
    if(isAvailable()){
        state = ARM;
        PP.reset();
    }
}

void Operator::takeOff()
{
    if(isAvailable())
        state = TAKE_OFF;
}

void Operator::emergencyLanding()
{
    state = EMERGENCY_LANDING;
    controller.disconnect();
}
