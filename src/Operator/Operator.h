
#ifndef OPERATOR_H
#define OPERATOR_H

#include "Controller/Controller.h"
#include "ProgramPlayer/ProgramPlayer.h"
#include "Operator/StateWin/StateWin.h"
#include "config.h"


enum OPERATOR_STATE { EMERGENCY_LANDING, IDLE_GROUND, IDLE_AIR, ARM, TAKE_OFF, LAND };

class Operator
{
    DEBUG_PRINT_SERIAL* serial; 
    LiveDelay debugLiveDelay;

    // Program player
    ProgramPlayer PP;

    // throttel PID vars
    // TODO: implement a struct for PID variables
    
    
    // state related 
    //OPERATOR_STATE state; // the state of the operator
    Mission mission;

    StateWin stateWin;

    // boolean functions
    bool isAvailable() { return false; } // TO DELETE SAFLY!!!

public:
    void begin(DEBUG_PRINT_SERIAL& _serial);
    void loop();
    void setMission(const Mission& _mission){mission = _mission;}
    void emergencyLanding();
};

extern Operator OP;

#endif //OPERATOR_H