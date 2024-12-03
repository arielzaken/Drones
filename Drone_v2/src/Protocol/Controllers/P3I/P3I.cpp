#include "P3I.h"
#include <Arduino.h>

float P3I::update(float setpoint, float measured_value)
{
    static unsigned long int lastTime = millis();

    float error = setpoint-measured_value;
    float res = error * error * error * kp;// + acc * ki;
    if(millis() - lastTime >= 1000){
        Serial.print(error);
        Serial.print(" ");
        Serial.print(acc);
        Serial.print(" ");
        Serial.println(res);
        lastTime = millis();
    }

    acc = (acc + error > 100 || acc + error < -100) ? 0 : acc + error;

    return res;
}