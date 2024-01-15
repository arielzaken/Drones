#ifndef STATE_WIN_H
#define STATE_WIN_H
#include "Operator\State\State.h"

class StateWin
{
    State* currentState;
    
public:
    StateWin(State* startState);
    void loop();
};

#endif