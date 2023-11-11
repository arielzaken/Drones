
#ifndef OPERATOR_H
#define OPERATOR_H

#include "Controller/Controller.h"
#include "ProgramPlayer/ProgramPlayer.h"

#define MAX_ALT 2*100 // [cm]
#define DEBUG_PRINT_DELAY 400


enum OPERATOR_STATE { EMERGENCY_LANDING, IDLE_GROUND, IDLE_AIR, ARM, TAKE_OFF };

class Operator
{
    LiveDelay debugLiveDelay;

    // Program player
    ProgramPlayer PP;

    // flight parameters
    int32_t requiredAlt; // the required altitude of the drone
    
    // state related 
    OPERATOR_STATE state; // the state of the operator
    void printState();
    
    // internal calculasions
    uint16_t mapAltToThrottle(ALTITUDE_DATA); // map the altitude of the craft to throttle

    // boolean functions
    bool isAvailable() { return (state == IDLE_AIR || state == IDLE_GROUND); }

    // programs functions
    void takeOff(uint64_t time); // a privet function for takeoff 
    void arm(uint64_t time);

    // 

public:
    void begin();
    void loop();

    bool arm();
    bool takeOff();
    bool MoveRight();
    bool MoveLeft();
    bool MoveForward();
    bool MoveBackward();
    bool AdjustForwardToDirection();
    bool AdjustAttitude();
    bool Land();
    bool moveToPosition(int x, int y, int z);

    void emergencyLanding();
};

extern Operator OP;

#endif //OPERATOR_H