#pragma once
#include "Sensors/DistanceSensor/DistanceSensor.h"
#include "mock/ControllerMock/ControllerMock.h"
#include <Arduino.h>
#include <functional>

template <typename T>
class SensorMock : public Sensor_I<T> {
    std::function<T>& hook;
    bool initialized = false;
public:
    SensorMock(std::function<T>& _hook) : hook(){
        if(_hook != nullptr){
            hook = _hook;
            initialized = true;
        }
    }
    /// @brief this func is for the Sensor_I interface
    /// @return on success the res of the hooked func, on failure T()
    virtual T read() override {
        if(initialized) return hook();
    }
};