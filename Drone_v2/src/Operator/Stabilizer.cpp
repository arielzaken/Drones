#include "Stabilizer.h"

Velocity Stabilizer::calcTwist()
{
    Velocity res;
    for (size_t i = 0; i < numOfBehaviors; i++){
        if(behaviors[i] != nullptr){
            res += behaviors[i]->calcBehavior();
        }
    }
    return res;
}

Stabilizer::Stabilizer()
{
    memset(behaviors, 0, sizeof(Behavior_I*) * STABILIZER_NUM_OF_BEHAVIORS);
    numOfBehaviors = 0;
}

uint8_t Stabilizer::addBehavior(Behavior_I &behavior)
{
    if(numOfBehaviors <= STABILIZER_NUM_OF_BEHAVIORS-1){
        for(size_t i = 0; i < STABILIZER_NUM_OF_BEHAVIORS; i++){
            if(!behaviors[i]){
                behaviors[i] = &behavior;
                behavior.setup();
                numOfBehaviors++;
                return i;
            }
        }
    }
    return 0;
}

void Stabilizer::removeBehavior(uint8_t discriptor)
{
    behaviors[discriptor] = nullptr;
}

void Stabilizer::setDroneController(const DroneController_I &controller)
{
    droneController = controller;
}

void Stabilizer::setVelocitySensor(const VelocitySensor &sensor)
{
    velocitySensor = sensor;
}

void Stabilizer::setController(const Controller_t &con)
{
    controller = con;
}

void stabilizerLoop(void *arg)
{
    Stabilizer* This = static_cast<Stabilizer*>(arg);
    Velocity twist = This->calcTwist();
    for(;;) {
        Velocity currVel = This->velocitySensor.read();
        Twist<uint16_t> command = This->controller.update(twist ,currVel);
        This->droneController.setThrottle(command[Z]);
        This->droneController.setPitch(command[W]);
        This->droneController.setYaw(command[Y]);
        This->droneController.setRoll(command[X]);
        delay(4);
    }
}
