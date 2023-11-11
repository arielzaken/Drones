#include "Operator.h"

Operator OP;

void Operator::printState()
{
    Serial.print("current state: ");
    switch(state){
    case EMERGENCY_LANDING:
        Serial.println("EMERGENCY_LANDING");
        break;
    case IDLE_GROUND:
        Serial.println("IDLE_GROUND");
        break;
    case IDLE_AIR:
        Serial.println("IDLE_AIR");
        break;
    case ARM:
        Serial.println("ARM");
        break;
    case TAKE_OFF:
        Serial.println("TAKE_OFF");
        break;
    default:
        Serial.println("UNKNOWN");
        break;
    }
}

uint16_t Operator::mapAltToThrottle(ALTITUDE_DATA alt)
{
    return controller.getThrottle() + (alt.EstAlt);
}

void Operator::takeOff(uint64_t time)
{
}

void Operator::arm(uint64_t time)
{   
    if(time<=1000 && time >= 800){
        controller.disarm();
    }
    else if(time>=7000){
        controller.arm();
        state = IDLE_GROUND;
    }
}

/// @brief this func init the operator. (without delay to avoid BAD-RX-timeout)
void Operator::begin()
{
    controller.begin();
    debugLiveDelay.setDelay(DEBUG_PRINT_DELAY);
    state = IDLE_GROUND;
    if(arm())
        Serial.println("arming...");
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
        break;
    case IDLE_GROUND:
        break;
    case EMERGENCY_LANDING:
        break;
    }
    ALTITUDE_DATA alt = controller.getAltitude();
    if(controller.isArmed() && alt.EstAlt >= MAX_ALT)
        emergencyLanding();
    
    if(debugLiveDelay.tryToActivate())
        printState();
    controller.loop();
}

bool Operator::arm()
{
    if(isAvailable()){
        state = ARM;
        PP.reset();
        return true;
    }
    return false;
}

bool Operator::takeOff()
{
    if(isAvailable()){
        state = TAKE_OFF;
        PP.reset();
        return true;
    }
    return false;
}

void Operator::emergencyLanding()
{
    state = EMERGENCY_LANDING;
    controller.disconnect();
}
