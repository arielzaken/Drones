// #include "Adafruit_VL53L0X.h"
// #include "Sensors/CashProxy/SensorCashProxy.h"
// #include "mock/SensorMock/SensorMock.h"
// #include "mock/ControllerMock/ControllerMock.h"
// #include "Operator/Stabilizer.h"
// #include "Operator/Behaviors/HoverBehavior/HoverBehavior.h"
// #include "Protocol/Controllers/VelPPPI/VelPPPI.h"
#include "Arduino.h"

// ControllerMock CM;

// SensorMock<uint16_t> altSensor([&]() { return (int32_t)(CM.getPos()[Z] * 100); });

// SensorMock<Velocity> velSensor([&]() { return CM.getVelocity(); });

// VelPPPI cont(1, 5);

// Stabilizer stab(
//     (DroneController_I&)CM,
//     (Controller_t&)cont,
//     (VelocitySensor&)velSensor
//     );

// HoverBehavior hover_B((DistanceSensor&)altSensor, 2000);
// uint8_t hover_bd;

void setup() {
	Serial.begin(115200);
    // CM.enable();

    // hover_bd = stab.addBehavior(hover_B);
}

void loop() {
    // CM.print();
    delay(300);
}


// #include "Adafruit_VL53L0X.h"

// Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// void setup() {
//   Serial.begin(115200);

//   // wait until serial port opens for native USB devices
//   while (! Serial) {
//     delay(1);
//   }
  
//   Serial.println("Adafruit VL53L0X test");
//   if (!lox.begin()) {
//     Serial.println(F("Failed to boot VL53L0X"));
//     while(1);
//   }
//   // power 
//   Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
// }


// void loop() {
//   VL53L0X_RangingMeasurementData_t measure;
    
//   Serial.print("Reading a measurement... ");
//   lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

//   if (measure.RangeStatus != 4) {  // phase failures have incorrect data
//     Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
//   } else {
//     Serial.println(" out of range ");
//   }
    
//   delay(100);
// }
