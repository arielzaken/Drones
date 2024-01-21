#ifndef STATES_H
#define STATES_H
#include "State.h"


State IdleGround(
    [](){ // isOkToNext
        return false;
    }, 
    [](){ // loop

    });
State TakeOff([](){return false;}, [](){});
State InTransit([](){return false;}, [](){});
State Land([](){return false;}, [](){});

#endif