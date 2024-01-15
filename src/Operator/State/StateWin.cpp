#include "StateWin.h"

void StateWin::loop()
{
    if(currentState->IsOkToNext())
        currentState = currentState->getNextState();

}