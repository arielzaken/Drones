#include "StateWin.h"

StateWin::StateWin(State *startState, Mission* _mission): currentState(startState), mission(_mission)
{

}

void StateWin::deleteStates(){
    State* delPointer = currentState->getNextState();
    while(delPointer != currentState){
        State* temp = delPointer->getNextState();
        delete delPointer;
        delPointer = temp;
    }
    delete delPointer;
    currentState = nullptr;
}

StateWin::~StateWin()
{
    deleteStates();
}

void StateWin::inisialize()
{
    if (currentState)
        deleteStates();
    State* gndState = new State("gnd", 
        [](){ // isOkToNext
            return false;
        }, [](){ // loop

        });
    State* takeOffState = new State("tof", 
        [](){ // isOkToNext
            return false;
        }, [](){ // loop
            
        });
    State* inTransitState = new State("trn", 
        [](){ // isOkToNext
            return false;
        }, [](){ // loop

        });
    State* landState = new State("lnd", 
        [](){ // isOkToNext
            return false;
        }, [](){ // loop

        });
    gndState->setNextState(takeOffState);
    takeOffState->setNextState(inTransitState);
    inTransitState->setNextState(landState);
    landState->setNextState(gndState);
    currentState = gndState;
}

void StateWin::loop()
{
    currentState->loop();
    if(currentState->IsOkToNext())
        currentState = currentState->getNextState();

}