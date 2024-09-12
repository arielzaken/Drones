#pragma once
#include "Sensors/Sensor_I.h"
#include <stdint.h>

template <typename T>
class SensorCashProxy : public Sensor_I<T>{
    /**
     * the pointer to the sensor object
     */
    Sensor_I<T>* m_pSensor;
    T data;
    /**
     * the max time in ms that a sensor data is still considerd fresh
     */
    uint16_t spoilTime;
    static void proxyLoop(void* args);
public:
    SensorCashProxy(Sensor_I<T>* m_pSensor, uint16_t spoilTime);
    T read() override;
};
