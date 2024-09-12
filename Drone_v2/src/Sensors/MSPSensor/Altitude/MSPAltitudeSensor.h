#pragma once

#include "Sensors/MSPSensor/MSPSensor.h"
#include "Sensors/MSPSensor/Altitude/MSPAltitudeResult.h"
class MSPAltitudeSensor : public MSPSensor{
    MSPAltitudeResult m_result;
public:
    virtual int sensorCode() override { return MSP_ALTITUDE; }
    virtual MSPResult* getInstance() override { return &m_result;}
};