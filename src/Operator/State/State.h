#ifndef STATE_H
#define STATE_H
#include "Controller\Controller.h" 
#include "Operator\Mission\Mission.h"

class State
{
protected:
    char name[4];
    State* nextState;
    Mission* mission; //TEMP!! TO REMOVE!! 
    bool (*ptrIsOkToNext)();
    void (*ptrLoop)();
public:
    State(const char* name, bool (*ptrIsOkToNext)(), void (*ptrLoop)());
    char* getName() { return name; }
    State* getNextState() { return nextState; }
    void setNextState(State* state) { nextState = state; }
    bool IsOkToNext();
    void loop();
};



#endif // STATE_H