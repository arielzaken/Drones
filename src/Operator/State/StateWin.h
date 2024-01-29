#ifndef STATE_WIN_H
#define STATE_WIN_H
#include "Operator\State\State.h"
#include "Operator\Mission\Mission.h"

class StateWin
{
    State* currentState;
    Mission* mission;
    void deleteStates();
public:
    StateWin(State* startState, Mission* _mission);
    ~StateWin();
    void inisialize();
    void loop();
};

#endif