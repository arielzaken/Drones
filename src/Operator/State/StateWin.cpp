#include "StateWin.h"

StateWin::StateWin(Mission* _mission): currentState(nullptr)
{
    if(_mission != nullptr)
        mission = _mission;
    
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
        [](){ if(mission!=NULL) return true;// isOkToNext
            return false;
        }, [](uint64_t time){ // loop

        }, mission);
    State* takeOffState = new State("tof", 
        [](){return(Controller.getAltitude.equalAltitude(requiredAlt)) // isOkToNext
        }, [](uint64_t time){ // loop

        }, mission);
    State* inTransitState = new State("trn", 
        [](){if(Controller.getRawGPS) // isOkToNext
            return false;
        }, [](uint64_t time){ // loop

        }, mission);
    State* landState = new State("lnd", 
        [](){ // isOkToNext
            return false;
        }, [](uint64_t time){ // loop

        }, mission);
    gndState->setNextState(takeOffState);
    takeOffState->setNextState(inTransitState);
    inTransitState->setNextState(landState);
    landState->setNextState(gndState);
    currentState = gndState;
int x =0;
}

void StateWin::loop()
{
    currentState->loop(PP.getTime());
    if(currentState->IsOkToNext()){
        currentState = currentState->getNextState();
        PP.reset();
    }

}