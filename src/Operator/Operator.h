
#ifndef OPERATOR_H
#define OPERATOR_H

#include "Controller/Controller.h"
#include "ProgramPlayer/ProgramPlayer.h"
#include "algorithems/PID/PID_v1.h"
#include "BluetoothSerial.h"

#define DEBUG_PRINT_DELAY 200

#define MAX_ALT 200 // [cm]
#define ALT_PID_P 5
#define ALT_PID_I 0
#define ALT_PID_D 0
#define H 5.0 // [m]

enum OPERATOR_STATE { EMERGENCY_LANDING, IDLE_GROUND, IDLE_AIR, ARM, TAKE_OFF, LAND };

class Operator
{
    HardwareSerial* serial; 
    BluetoothSerial* bluetoothSerial;
    LiveDelay debugLiveDelay;

    // Program player
    ProgramPlayer PP;

    // throttel PID vars
    // TODO: implement a struct for PID variables
    double requiredAlt; // the required altitude of the drone
    double currentAlt; // the curent altitude of the drone
    double hoverThrottle; // throttle
    PID altPID = PID(&currentAlt, &hoverThrottle, &requiredAlt, (double)ALT_PID_P, (double)ALT_PID_I, (double)ALT_PID_D, P_ON_E, DIRECT);
    
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
    void land(uint64_t time);

public:
    void begin(HardwareSerial& _serial, BluetoothSerial& _bluetooth);
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