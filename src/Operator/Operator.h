
#ifndef OPERATOR_H
#define OPERATOR_H

#include "Controller/Controller.h"
#include "Operator/Mission/Mission.h"
#include "ProgramPlayer/ProgramPlayer.h"
#include "algorithems/PID/PID_v1.h"
#include "BluetoothSerial.h"
#include "Operator/StateWin/StateWin.h"
#include "config.h"


enum OPERATOR_STATE { EMERGENCY_LANDING, IDLE_GROUND, IDLE_AIR, ARM, TAKE_OFF, LAND };

class Operator
{
    DEBUG_PRINT_SERIAL* serial; 
    LiveDelay debugLiveDelay;

    // throttel PID vars
    // TODO: implement a struct for PID variables
    double requiredAlt; // the required altitude of the drone
    double currentAlt; // the curent altitude of the drone
    double hoverThrottle; // throttle
    PID altPID = PID(
        &currentAlt, 
        &hoverThrottle, 
        &requiredAlt, 
        (double)ALT_PID_P, 
        (double)ALT_PID_I, 
        (double)ALT_PID_D, 
        P_ON_E, DIRECT);
    
    // state related 
    Mission mission;
    StateWin winState = StateWin(&mission); // the state of the operator
    void printState();

    // programs functions
    void takeOff(uint64_t time); // a privet function for takeoff 
    void arm(uint64_t time);
    void land(uint64_t time);

public:
    void begin(DEBUG_PRINT_SERIAL& _serial);
    void loop();

    bool arm();
    bool takeOff();
    bool MoveRight();
    bool MoveLeft();
    bool MoveForward();
    bool MoveBackward();
    bool AdjustForwardToDirection();
    bool AdjustAttitude();
    bool land();
    bool moveToPosition(int x, int y, int z);

    void emergencyLanding();
};

extern Operator OP;

#endif //OPERATOR_H