#pragma once
#include "Operator/Behavior_I.h"
#include "DroneController/DroneController_I.h"
#include "Sensors/VelocitySensor/VelocitySensor.h"
#include "Protocol/Controllers/Controller_I.h"
#include "config.h"

typedef Controller_I<Twist<uint16_t>,Velocity> Controller_t;

class Stabilizer
{
    Behavior_I* behaviors[STABILIZER_NUM_OF_BEHAVIORS];
    uint8_t numOfBehaviors;
    DroneController_I& droneController;
    Controller_t& controller;
    VelocitySensor& velocitySensor;
    
    Velocity calcTwist();
public:
    Stabilizer(
        DroneController_I& _droneController,
        Controller_t& _controller,
        VelocitySensor& _velocitySensor
        );
    /**
     * add a new behavior mid-run to the stablizer 
     * @param behavior the new behavior to add
     * @return a discriptor for the behavior that was added
     */
    uint8_t addBehavior(Behavior_I& behavior);
    /**
     * remove a behavior mid-run from the stablizer
     * @param discriptor the discriptor we got from the addBehavior method to remove the behavior.
     */
    void removeBehavior(uint8_t discriptor);

    friend void stabilizerLoop(void* This);
};
