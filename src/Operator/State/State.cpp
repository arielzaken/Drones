#include "State.h"
#include <stdio.h>

State::State(const char* _name, bool (*_ptrIsOkToNext)(), void (*_ptrLoop)())
    :ptrIsOkToNext(_ptrIsOkToNext), ptrLoop(_ptrLoop), nextState(nullptr), mission(nullptr) 
{
    strncpy(this->name, _name, sizeof(this->name));
}

bool State::IsOkToNext()
{
    return ptrIsOkToNext();
}

void State::loop()
{
    return ptrLoop();
}
