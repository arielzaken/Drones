#include "Adafruit_VL53L0X.h"
// #include "Sensors/CashProxy/SensorCashProxy.h"
#include "Sensors/DistanceSensor/I2CLaserDistanceSensor/I2CLaserDistanceSensor.h"
#include "Arduino.h"
I2CLaserDistanceSensor real_lox;

// SensorCashProxy<uint16_t> lox(real_lox, 1000);

void setup() {
	Serial.begin(115200);
}

void loop() {
    Serial.print("Distance: ");
    //Serial.print(lox.read());
    Serial.println(" cm");
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
