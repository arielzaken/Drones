#include "Operator.h"

Operator OP;

void Operator::printState()
{
    serial->print("current state: ");
    switch(state){
    case EMERGENCY_LANDING:
        serial->println("EMERGENCY_LANDING");
        break;
    case IDLE_GROUND:
        serial->println("IDLE_GROUND");
        break;
    case IDLE_AIR:
        serial->println("IDLE_AIR");
        break;
    case ARM:
        serial->println("ARM");
        break;
    case TAKE_OFF:
        serial->println("TAKE_OFF");
        break;
    default:
        serial->println("UNKNOWN");
        break;
    }
}

void Operator::takeOff(uint64_t time)
{
    if(controller.isArmed()){
        if(time < 3000)
            controller.setThrottle(map(time,0,3000,1000,1250));
        else
            state = IDLE_AIR;
    }
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
void Operator::begin(HardwareSerial& _serial)
{
    // inisialize the serial object
    this->serial = &_serial;

    // begin the controller
    controller.begin();

    // initialize the debugLiveDelay
    debugLiveDelay.setDelay(DEBUG_PRINT_DELAY);

    //PID setup
    altPID.SetMode(AUTOMATIC);
    altPID.SetOutputLimits(-100, 100);
    requiredAlt = 2.0;
    state = IDLE_GROUND; 

    // self arming
    if(arm())
        serial->println("armed");
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

    if(state != EMERGENCY_LANDING){
        // get sensors values
        ALTITUDE_DATA alt = controller.getAltitude();
        currentAlt = alt.EstAlt/100.f; // in meters

        // altitude hold PID
        if(state != IDLE_GROUND && state != TAKE_OFF && state != ARM){
            altPID.Compute();
            serial->printf("thr: % 7.3f | alt: % 7.3f\n",1250 + hoverThrottle, currentAlt);
        }

        // emergency landing 
        if(controller.isArmed() && alt.EstAlt >= MAX_ALT){
            emergencyLanding();
            serial->printf("emergency landing: alt = %d\n", currentAlt);
        }
        
        // print the current state
        if(debugLiveDelay.tryToActivate()){
            printState();
        }
    }
    
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
