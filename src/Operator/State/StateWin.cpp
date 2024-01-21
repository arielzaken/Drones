#include "StateWin.h"

StateWin::StateWin(State *startState): currentState(startState)
{

}

void StateWin::loop()
{
    currentState->loop();
    if(currentState->IsOkToNext())
        currentState = currentState->getNextState();

}