#include "State.h"
#include <stdio.h>

State::State(const char* _name, std::function<void(uint64_t, Mission*)> _Loop, Mission* _mission)
    :loopFunc(_Loop), mission(_mission)
{
    strncpy(this->name, _name, sizeof(this->name));
}

void State::loop(uint64_t time)
{
    loopFunc(time, mission);
}
