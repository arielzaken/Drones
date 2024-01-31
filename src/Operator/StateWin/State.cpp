#include "State.h"
#include <stdio.h>

State::State(const char* _name, void (*_ptrLoop)(uint64_t time, Mission* mission), Mission* _mission)
    :ptrLoop(_ptrLoop), mission(_mission)
{
    strncpy(this->name, _name, sizeof(this->name));
}

void State::loop(uint64_t time)
{
    return ptrLoop(time, mission);
}
