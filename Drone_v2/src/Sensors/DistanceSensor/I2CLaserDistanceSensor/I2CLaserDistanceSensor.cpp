#include "I2CLaserDistanceSensor.h"
#include <Adafruit_VL53L0X.h>

I2CLaserDistanceSensor::I2CLaserDistanceSensor()
{
    lox = new Adafruit_VL53L0X();
    initialize();
}

I2CLaserDistanceSensor::~I2CLaserDistanceSensor()
{
    delete lox;
    lox = nullptr;
}

void I2CLaserDistanceSensor::initialize(uint8_t address)
{
                      lox->begin(address);
    lox->configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_LONG_RANGE);
}

uint16_t I2CLaserDistanceSensor::read()
{
    VL53L0X_RangingMeasurementData_t measure1;
    lox->rangingTest(&measure1);
    if(measure1.RangeStatus != 4)      // if not out of range
        return measure1.RangeMilliMeter;
    return UINT16_MAX;
}