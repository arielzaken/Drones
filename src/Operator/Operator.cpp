#include "Operator.h"

Operator OP;

void Operator::printState()
{
    switch(state){
    case EMERGENCY_LANDING:
        this->bluetoothSerial->println("EMERGENCY_LANDING");
        break;
    case IDLE_GROUND:
        this->bluetoothSerial->println("IDLE_GROUND");
        break;
    case IDLE_AIR:
        this->bluetoothSerial->println("IDLE_AIR");
        break;
    case ARM:
        this->bluetoothSerial->println("ARM");
        break;
    case TAKE_OFF:
        this->bluetoothSerial->println("TAKE_OFF");
        break;
    default:
        this->bluetoothSerial->println("UNKNOWN");
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

void Operator::land(uint64_t time)
{   
    if(time<=3000){
        controller.setThrottle(1230);
    }
    else{
        controller.disarm();
        state = IDLE_GROUND;
    }
}

/// @brief this func init the operator. (without delay to avoid BAD-RX-timeout)
void Operator::begin(HardwareSerial& _serial, BluetoothSerial& _bluetooth)
{
    // inisialize the serial object
    this->serial = &_serial;
    this->bluetoothSerial = &_bluetooth;

    // begin the controller
    controller.begin();

    // initialize the debugLiveDelay
    debugLiveDelay.setDelay(DEBUG_PRINT_DELAY);

    //PID setup
    altPID.SetMode(AUTOMATIC);
    altPID.SetOutputLimits((double)-100, (double)100);
    requiredAlt = H;
    state = IDLE_GROUND; 

    // self arming
    if(arm())
        this->bluetoothSerial->println("armed");
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
    case LAND:
        land(PP.getTime());
        break;
    case IDLE_AIR:
        break;
    case IDLE_GROUND:
        break;
    case EMERGENCY_LANDING:
        break;
    }

    // get sensors values
    ALTITUDE_DATA alt = controller.getAltitude();

    if(state != EMERGENCY_LANDING){
        // emergency landing 
        currentAlt = alt.EstAlt/100.f; // in meters

        if(controller.isArmed() && alt.EstAlt >= MAX_ALT){
            emergencyLanding();     
        }
        // altitude hold PID

        if(state != IDLE_GROUND && state != TAKE_OFF && state != ARM && state != LAND){
            altPID.Compute();
            controller.setThrottle(1250 + hoverThrottle);
            if(debugLiveDelay.tryToActivate()){
                this->bluetoothSerial->printf("thr: % 7.3f | alt: % 7.3f\n",1250 + hoverThrottle, currentAlt);
                printState();
            }
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

bool Operator::land()
{
    if(isAvailable()){
        state = LAND;
        PP.reset();
        return true;
    }
    return false;
}

void Operator::emergencyLanding()
{
    state = EMERGENCY_LANDING;
    ALTITUDE_DATA alt = controller.getAltitude();
    land();
    this->bluetoothSerial->printf("emergency landing: alt = %d\n", alt.EstAlt);
    //controller.disconnect();
}
