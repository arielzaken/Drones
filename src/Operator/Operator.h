
#ifndef OPERATOR_H
#define OPERATOR_H

#include "Controller/Controller.h"

#define MAX_ALT 10*100 // [cm]

enum OPERATOR_STATE { IDLE_GROUND, IDLE_AIR ,TAKE_OFF, EMERGENCY_LANDING};

class Operator
{
    uint32_t requiredAlt; // the required altitude of the drone
    uint32_t startAlt; // the starting altitude of the drone
    OPERATOR_STATE state; // the state of the operator
    
    uint16_t mapAltToThrottle(ALTITUDE_DATA); // map the altitude of the craft to throttle
public:
    void begin();
    void loop();
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