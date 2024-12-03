#include "mock/SensorMock/SensorMock.h"
#include "mock/ControllerMock/ControllerMock.h"
#include "Operator/Stabilizer.h"
#include "Operator/Behaviors/HoverBehavior/HoverBehavior.h"
#include "Protocol/Controllers/VelP3I/VelP3I.h"
#include "Arduino.h"

ControllerMock CM;

SensorMock<uint16_t> altSensor([&]() { return (int32_t)(CM.getPos()[Z] * 100); });

SensorMock<Velocity> velSensor([&]() { return CM.getVelocity(); });

VelP3I cont(1, 5);

Stabilizer stab(
    (DroneController_I&)CM,
    (Controller_t&)cont,
    (VelocitySensor&)velSensor
    );

HoverBehavior hover_B((DistanceSensor&)altSensor, 2000);
uint8_t hover_bd;

void setup() {
	Serial.begin(115200);
    CM.enable();

    hover_bd = stab.addBehavior(hover_B);
}

void loop() {
    CM.print();
    delay(300);
}