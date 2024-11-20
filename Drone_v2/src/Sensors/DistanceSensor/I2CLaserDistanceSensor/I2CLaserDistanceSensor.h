#pragma once
#include "Sensors/DistanceSensor/DistanceSensor.h"
#include <Adafruit_VL53L0X.h>

class I2CLaserDistanceSensor : public DistanceSensor
{
    Adafruit_VL53L0X *lox;
public:
    I2CLaserDistanceSensor();
    ~I2CLaserDistanceSensor();
    void initialize(uint8_t address = VL53L0X_I2C_ADDR);
    virtual uint16_t read() override;
};