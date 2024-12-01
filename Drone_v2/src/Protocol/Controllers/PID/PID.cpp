#include "PID.h"
#include <Arduino.h>

int32_t clamp(int32_t value, int32_t min, int32_t max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

PID::PID(int32_t p, int32_t i, int32_t d, int32_t max_value) : 
    kp(p), ki(i), kd(d),
    max_value(max_value), 
    error(0), prev_error(0), 
    integral(0), output(0) 
{
    lastTime = millis();
}

int32_t PID::update(int32_t setpoint, int32_t measured_value)
{
    uint64_t now = millis();
    uint32_t dt = now - lastTime;
    if(dt >= 50){
        lastTime = now;
        return 0;
    }
    error = setpoint - measured_value;
    int32_t temp = integral + (error * dt);
    integral = (temp > 300000 || temp < -300000) ? integral : temp;
    int32_t derivative = (error - prev_error) / (int32_t)dt;
    output = kp * error + ki * integral + kd * derivative;
    // Serial.print("dt:");
    // Serial.println(dt);
    // Serial.print("e:");
    // Serial.println(error);
    // Serial.print("ti:");
    // Serial.println(temp);
    // Serial.print("d:");
    // Serial.println(derivative);
    // Serial.print("o:");
    // Serial.println(output);
    prev_error = error;
    lastTime = now;
    output = clamp(output >> 7, -max_value, max_value); // Limit the output to -200 to 200
    return output;
}
