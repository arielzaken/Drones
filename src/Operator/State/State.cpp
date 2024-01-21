#include "State.h"
#include <stdio.h>

char *State::get_name()
{
    return name;
}

/****************************************************************/

bool IdleGround::isOkToNext()
{
    if(mission!=NULL)
        return true;
    return false;
}

bool IdleGround::loop()
{
    
    return false;
}

/****************************************************************/

bool TakeOff::isOkToNext()
{
    if(Controller.equalAltitude())
        return true
    return false;
}

bool TakeOff::loop()
{
    return false;
}

/****************************************************************/

bool Transfer::isOkToNext()
{
    if(mission.end_point)
    return false;
}

bool Transfer::loop()
{
    return false;
}

/****************************************************************/

bool Land::isOkToNext()
{
    return false;
}

bool Land::loop()
{
    return false;
}

State::State(, void (*ptrLoop)())
{
}

bool State::IsOkToNext()
{
    return (*ptrIsOkToNext)();
}

void State::loop()
{
    return (*ptrLoop)();
}
