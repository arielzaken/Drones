#ifndef STATE_H
#define STATE_H
#include "Controller\Controller.h" 
#include "Operator\Mission\Mission.h"

class State
{
    char name[4];
    Mission* mission;
    std::function<void(uint64_t, Mission*)> loopFunc;
public:
    /**
     * @param name the name of the state 3 lettrs
     * @param loopFunc the function to be called when i want to loop. gets the pointer to the mission 
     * @param mission a pointer to the mission
    */
    State(
        const char* name,
        std::function<void(uint64_t, Mission*)> loopFunc,
        Mission* mission);
public:
    char* getName() { return name; }
    void loop(uint64_t time);
};



#endif // STATE_H