#include "Sensors/CashProxy/SensorCashProxy.h"
#include "SensorCashProxy.h"
#include <RTOS.h>

template <typename T>
struct sensor_loop_args_t {
    Sensor_I<T>* sensor;
    uint16_t spoil;
    T* data;
};


template <typename T>
void SensorCashProxy<T>::proxyLoop(void *_args)
{
    sensor_loop_args_t<T>* args = static_cast<sensor_loop_args_t<T>*>(_args);
    Sensor_I<T>* sensor = args->sensor;
    uint16_t spoil = args->spoil;
    T* data = args->data;
    for(;;){
        *(data) = sensor->read();
        vTaskDelay(spoil/portTICK_PERIOD_MS);
    }
}

template <typename T>
SensorCashProxy<T>::SensorCashProxy(Sensor_I<T> *_m_pSensor, uint16_t _spoilTime)
{
    m_pSensor = _m_pSensor;
    spoilTime = _spoilTime;
    xTaskCreate(

    )
}



template <typename T>
T SensorCashProxy<T>::read()
{
    return data;
}