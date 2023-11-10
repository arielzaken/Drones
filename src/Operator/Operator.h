
#ifndef OPERATOR_H
#define OPERATOR_H

#include "Controller/Controller.h"
#include "ProgramPlayer/ProgramPlayer.h"

#define MAX_ALT 10*100 // [cm]

enum OPERATOR_STATE { EMERGENCY_LANDING, IDLE_GROUND, IDLE_AIR, ARM, TAKE_OFF };

class Operator
{
    // Program player
    ProgramPlayer PP;

    // flight parameters
    uint32_t requiredAlt; // the required altitude of the drone
    uint32_t startAlt; // the starting altitude of the drone
    
    // state related 
    OPERATOR_STATE state; // the state of the operator
    
    // internal calculasions
    uint16_t mapAltToThrottle(ALTITUDE_DATA); // map the altitude of the craft to throttle

    // boolean functions
    bool isAvailable() { return (state == EMERGENCY_LANDING); }

    // programs functions
    void takeOff(uint64_t time); // a privet function for takeoff 
    void arm(uint64_t time);

    // 

public:
    void begin();
    void loop();
    void arm();
    void takeOff();
    void MoveRight();
    void MoveLeft();
    void MoveForward();
    void MoveBackward();
    void AdjustForwardToDirection();
    void AdjustAttitude();
    void Land();
    void moveToPosition(int x, int y, int z);
    void emergencyLanding();
};

extern Operator OP;

#endif //OPERATOR_H