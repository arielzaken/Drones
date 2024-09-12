#pragma once

template <typename T>
class Sensor_I{
    virtual T read() = 0;
};