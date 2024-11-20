#pragma once
#include "Sensors/DistanceSensor/DistanceSensor.h"
#include <Arduino.h>
class disMock : public DistanceSensor {
public:
    virtual uint16_t read() override {
        return 5;
    }
};