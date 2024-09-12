#pragma once
#include "Protocol/MSP/Msp.h"
#include "Sensors/MSPSensor/MSPResult.h"
#include "Sensors/Sensor_I.h"

class MSPSensor : public Sensor_I<MSPResult*>
{
public:
    /**
     * template method for reading a MSP sensor data.
     * @return a pointer to the sensor data structure if successful, otherwise nullptr.
     */
    virtual MSPResult* read() override;
    /**
     * a hook function for setting the packet type
     * @example sensorCode() { return MSP_ALTITUDE; }
     */
    virtual int sensorCode() = 0;
    /**
     * a hook function to give the real packet data structure to the sensor
     */
    virtual MSPResult* getInstance() = 0;
};
