#include "UltraSonicDistanceSensor.h"
#include <esp32-hal-gpio.h>
#include <Arduino.h>
uint16_t UltraSonicDistanceSensor::read()
{
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    // Calculating the distance
    return pulseIn(echo, HIGH) * 0.034 / 2;
}