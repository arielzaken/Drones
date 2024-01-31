#include "Operator.h"

void Operator::takeOff(uint64_t time)
{
    if(controller.isArmed()){
        if(time < 3000)
            controller.setThrottle(map(time,0,3000,1000,1250));
    }
}

void Operator::arm(uint64_t time)
{
    if(time<=1000 && time >= 800){
        controller.disarm();
    }
    else if(time>=7000){
        controller.arm();
        //state = IDLE_GROUND;
    }
}

void Operator::land(uint64_t time)
{   
    if(time<=3000){
        controller.setThrottle(1230);
    }
    else{
        controller.disarm();
        //state = IDLE_GROUND;
    }
}

/// @brief this func init the operator. (without delay to avoid BAD-RX-timeout)
void Operator::begin(DEBUG_PRINT_SERIAL& _serial)
{
    // inisialize the serial object
    this->serial = &_serial;

    // begin the controller
    controller.begin();

    // initialize the debugLiveDelay
    debugLiveDelay.setDelay(DEBUG_PRINT_DELAY);

    //PID setup
    altPID.SetMode(AUTOMATIC);
    altPID.SetOutputLimits((double)-100, (double)100);
    requiredAlt = H; 

    // self arming
    if(arm())
        this->serial->println("armed");
}

void Operator::loop()
{
    winState.loop();
    // get alt value
    ALTITUDE_DATA alt = controller.getAltitude();

    // emargency landing
    if(controller.isArmed() && alt.EstAlt >= MAX_ALT){
        emergencyLanding();     
    }

    if(/*is state implements hold alt*/){
        currentAlt = alt.EstAlt/100.f; // in meters
        altPID.Compute();
        controller.setThrottle(1250 + hoverThrottle);
        if(debugLiveDelay.tryToActivate()){
            this->serial->printf("thr: % 7.3f | alt: % 7.3f\n", 1250 + hoverThrottle, currentAlt);
            printState();
        }
    }

    controller.loop();
}

void Operator::emergencyLanding()
{
    ALTITUDE_DATA alt = controller.getAltitude();
    land();
    this->serial->printf("emergency landing: alt = %d\n", alt.EstAlt);
    //controller.disconnect();
}
