#pragma once
#include "Sensors/DistanceSensor/DistanceSensor.h"
#include <Adafruit_VL53L0X.h>

class I2CLaserDistanceSensor : public DistanceSensor
{
    Adafruit_VL53L0X lox;
public:
    void initialize(uint8_t address);
    virtual uint16_t read() override;
};