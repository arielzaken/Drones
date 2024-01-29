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
    void (*ptrLoop)(uint64_t time);
public:
    State(const char* name, bool (*ptrIsOkToNext)(), void (*ptrLoop)(uint64_t time), Mission* mission);
    char* getName() { return name; }
    State* getNextState() { return nextState; }
    void setNextState(State* state) { nextState = state; }
    bool IsOkToNext();
    void loop(uint64_t time);
};



#endif // STATE_H