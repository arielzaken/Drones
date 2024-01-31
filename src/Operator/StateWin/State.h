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
    bool (*ptrIsOkToNext)(Mission* mission);
    void (*ptrLoop)(uint64_t time, Mission* mission);
public:
    /**
     * @param name the name of the state 3 lettrs
     * @param ptrIsOkToNext the function to be called when i want to go to the next state. gets the pointer to the mission
     * @param ptrLoop the function to be called when i want to loop. gets the pointer to the mission 
     * @param mission a pointer to the mission
    */
    State(
        const char* name,
        bool (*ptrIsOkToNext)(Mission* mission), 
        void (*ptrLoop)(uint64_t time, Mission* mission),
        Mission* mission);
    char* getName() { return name; }
    State* getNextState() { return nextState; }
    void setNextState(State* state) { nextState = state; }
    bool IsOkToNext();
    void loop(uint64_t time);
};



#endif // STATE_H