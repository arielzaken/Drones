#include "Stabilizer.h"

void Stabilizer::calcBehaviors()
{
    for (size_t i = 0; i < numOfBehaviors; i += behaviors[i] != nullptr){
        if(behaviors[i] != nullptr){

            // TODO: implement behaviors summing.
        }
    }
    
}

uint8_t Stabilizer::addBehavior(Behavior_I &behavior)
{
    if(numOfBehaviors <= STABILIZER_NUM_OF_BEHAVIORS-1){
        for(size_t i = 0; i < STABILIZER_NUM_OF_BEHAVIORS; i++){
            if(!behaviors[i]){
                behaviors[i] = &behavior;
                return i;
            }
        }
    }
}

void Stabilizer::removeBehavior(uint8_t discriptor)
{
    behaviors[discriptor] = nullptr;
}
