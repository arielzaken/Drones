#pragma once
#include <stdint.h>
#include <bits/stdc++.h> 
#include "Protocol/Controllers/Controller_I.h"

class PID : public Controller_I<int32_t, int32_t>{
    int32_t kp, ki, kd;
    int32_t error, prev_error, integral;
    int32_t output;
    int32_t max_value;
    uint64_t lastTime;
public:
    PID(int32_t p, int32_t i, int32_t d,int32_t max_value);
    virtual int32_t update(int32_t setpoint, int32_t measured_value) override;
};