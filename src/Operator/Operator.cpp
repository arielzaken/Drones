#include "Operator.h"

Operator OP;

/// @brief this func init the operator. (without delay to avoid BAD-RX-timeout)
void Operator::begin(DEBUG_PRINT_SERIAL& _serial)
{
    // inisialize the serial object
    this->serial = &_serial;
    this->serial->println("Operator is online!");
    // begin the controller
    controller.begin();

    // initialize the debugLiveDelay
    debugLiveDelay.setDelay(DEBUG_PRINT_DELAY);

    stateWin.setup(&mission, this->serial);

    stateWin.insert(State("gnd",
        [this](uint64_t time, Mission* mission){
            if(time<=1000){
                controller.disableHover();
                controller.disarm();
            }
            if(mission->valid){
                this->stateWin.next();
            }
        }
        ,&mission));
    
    
    stateWin.insert(State("arm",
        [this](uint64_t time, Mission* mission){
            if(time < 200){
                controller.setThrottle(1000);
                controller.disarm();
            }
            else if(7000 <= time && time < 9000){
                controller.arm();
            }
            else if(9000 <= time){
                stateWin.next();
            }
        }
    ,&mission));

    stateWin.insert(State("tof",
        [this](uint64_t time, Mission* mission){
            if(time<=200){
                controller.enableHover();
                controller.setReqAlt((double)(HEIGHT_CHANNEL/100));
            }
            if(controller.getAltitude().equals(HEIGHT_CHANNEL)){
                stateWin.next();
            }
        }
    ,&mission));

    stateWin.insert(State("trn",
        [this](uint64_t time, Mission* mission){
            /*if(time < 200)
                controller.setYaw(FORWARD_YAW);*/
            /*if(controller.getRawGPS().equals(mission->end_point))
            */
            if(time >= 10000)
                stateWin.next();
        }
    ,&mission));

    stateWin.insert(State("lnd",
        [this](uint64_t time, Mission* mission){
            if(time <= 200){
                controller.setReqAlt((double)(0));
            }
            else if(controller.getAltitude().equals(0)){
                controller.disarm(); 
                mission->valid = false;
                stateWin.next();
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
        this->serial->printf("thr: %u | alt: %d ", controller.getThrottle(), alt.EstAlt);
        stateWin.printState();
    }
    controller.loop();
}

void Operator::emergencyLanding()
{
    //state = EMERGENCY_LANDING;
    ALTITUDE_DATA alt = controller.getAltitude();
    this->serial->printf("emergency landing: alt = %d\n", alt.EstAlt);
    controller.disconnect();
}