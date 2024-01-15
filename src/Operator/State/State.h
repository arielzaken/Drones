#ifndef STATE_H
#define STATE_H
#include "Controller\Controller.h" 
#include "Operator\Mission\Mission.h"

class State
{
protected:
    char name[3];
    State* nextState;
    Mission* mission; //TEMP!! TO REMOVE!! 
    bool (*ptrIsOkToNext)();
    void (*ptrLoop)();
public:
    State(bool (*ptrIsOkToNext)(), void (*ptrLoop)());
    char* getName() { return name; }
    State* getNextState() { return nextState; }
    bool IsOkToNext();
    void loop();
};


#endif // STATE_H