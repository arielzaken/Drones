#pragma once
#include "Sensors/DistanceSensor/DistanceSensor.h"

typedef uint8_t gpio_num;


class UltraSonicDistanceSensor : public DistanceSensor{
    gpio_num trigger;
    gpio_num echo;
public:
    UltraSonicDistanceSensor(gpio_num trigger_, gpio_num echo_):trigger(trigger_), echo(echo_) {}
    virtual uint16_t read() override;
};
