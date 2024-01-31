#include "Operator.h"

Operator OP;

/// @brief this func init the operator. (without delay to avoid BAD-RX-timeout)
void Operator::begin(DEBUG_PRINT_SERIAL& _serial)
{
    // inisialize the serial object
    this->serial = &_serial;

    // begin the controller
    controller.begin();

    // initialize the debugLiveDelay
    debugLiveDelay.setDelay(DEBUG_PRINT_DELAY);

    stateWin = StateWin(&mission, serial);
    stateWin.insert(State("gnd",
        [](uint64_t time, Mission* mission){
            if(time<=1000)
                controller.disableHover();
        }
    ,&mission));

    stateWin.insert(State("tof",
        [](uint64_t time, Mission* mission){
            if(time<=1000 && time >= 800){
                controller.disarm();
            }
            else if(time>=7000){
                controller.arm(); 

            }
        }
    ,&mission));

    stateWin.insert(State("trn",
        [](uint64_t time, Mission* mission){
            if(time<=1000 && time >= 800){
                controller.disarm();
            }
            else if(time>=7000){
                controller.arm(); 

            }
        }
    ,&mission));

    stateWin.insert(State("lnd",
        [](uint64_t time, Mission* mission){
            if(time<=1000 && time >= 800){
                controller.disarm();
            }
            else if(time>=7000){
                controller.arm(); 

            }
        }
    ,&mission));

    stateWin.reset();
}

void Operator::loop()
{
    // get sensors values
    ALTITUDE_DATA alt = controller.getAltitude();

    if(controller.isArmed() && alt.equals(MAX_ALT))
        emergencyLanding();     

    stateWin.loop();
    
    if(debugLiveDelay.tryToActivate()){
        this->serial->printf("thr: % 7.3f | alt: % 7.3f\n", controller.getThrottle(), alt.EstAlt);
        stateWin.printState();
    }
    controller.loop();
}

void Operator::emergencyLanding()
{
    //state = EMERGENCY_LANDING;
    ALTITUDE_DATA alt = controller.getAltitude();
    this->serial->printf("emergency landing: alt = %d\n", alt.EstAlt);
    //controller.disconnect();
}