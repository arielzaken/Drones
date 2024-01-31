#include "StateWin.h"
#include "Controller\Controller.h"

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
        [](Mission* mission){ // isOkToNext
            return mission!=NULL;
        }, [](uint64_t time, Mission* mission){ // loop
            // TODO: check if there is a mission
        }, mission);
    State* takeOffState = new State("tof", 
        [](Mission* mission){ // isOkToNext
            return controller.getAltitude().equals(HEIGHT_CHANNEL);
        }, [](uint64_t time, Mission* mission){ // loop
            
        }, mission);
    State* inTransitState = new State("trn", 
        [](Mission* mission){ // isOkToNext
            
            return Controller.getRawGPS();

        }, [](uint64_t time, Mission* mission){ // loop
            // TODO: check if there is a mission
        }, mission);
    State* landState = new State("lnd", 
        [](Mission* mission){ // isOkToNext
            
            return false;
        }, [](uint64_t time, Mission* mission){ // loop
            // TODO: check if there is a mission
        }, mission);

    gndState->setNextState(takeOffState);
    takeOffState->setNextState(inTransitState);
    inTransitState->setNextState(landState);
    landState->setNextState(gndState);
    currentState = gndState;
}

void StateWin::loop()
{
    currentState->loop(PP.getTime());
    if(currentState->IsOkToNext()){
        currentState = currentState->getNextState();
        PP.reset();
    }

}