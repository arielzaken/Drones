#include "State.h"
#include <stdio.h>

State::State(const char* _name, bool (*_ptrIsOkToNext)(Mission* mission), void (*_ptrLoop)(uint64_t time, Mission* mission), Mission* _mission)
    :ptrIsOkToNext(_ptrIsOkToNext), ptrLoop(_ptrLoop), nextState(nullptr), mission(_mission)
{
    strncpy(this->name, _name, sizeof(this->name));
}

bool State::IsOkToNext()
{
    return ptrIsOkToNext(mission);
}

void State::loop(uint64_t time)
{
    return ptrLoop(time, mission);
}
