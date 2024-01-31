#ifndef STATE_WIN_H
#define STATE_WIN_H
#include "Operator\State\State.h"
#include "Operator\Mission\Mission.h"
#include "Operator\ProgramPlayer\ProgramPlayer.h"

class StateWin
{
    State* currentState;
    Mission* mission;
    ProgramPlayer PP;
    void deleteStates();
public:
    StateWin(Mission* _mission);
    ~StateWin();
    void inisialize();
    void loop();
};

#endif