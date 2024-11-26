#pragma once

#include "DroneController/DroneControllerInterface.h"
#include "Operator/OperatorTypes.h"
#include <RTOS.h>
void mockControllerLoop(void* arg);
class ControllerMock : public DroneControllerInterface
{
private:
    Twist pos;
    uint16_t throttle = 1000; // the speed upwards throttle
    uint16_t pitch = 1500; // z axis rot
    uint16_t roll = 1500; // y axis rot
    uint16_t yaw = 1500; // x axis rot
    bool armed = false;
    TaskHandle_t taskHandle = nullptr;
public:
    virtual void setThrottle(uint16_t throttle) override;
    virtual void setPitch(uint16_t pitch) override;
    virtual void setYaw(uint16_t yaw) override;
    virtual void setRoll(uint16_t roll) override;
    virtual void setAUX(uint16_t channle, uint16_t auxValue) override;

    virtual void arm() override;
    virtual void disarm() override;
    virtual void disable() override;
    virtual void enable() override;

    void print(Print &);
    friend void mockControllerLoop(void* arg);
    Twist getPos();
};
