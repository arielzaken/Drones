#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Controller", true); // Set the Bluetooth name here

  Serial.println("Bluetooth Serial Started");

  while(!SerialBT.connect("clone_drone_in_the_danger_zone")) delay(1);
  Serial.println("connected to drone");
}

void loop() {
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  if (!SerialBT.connected()){
    Serial.println("connecting to drone...");
    while(!SerialBT.connect("clone_drone_in_the_danger_zone")) delay(1);
    Serial.println("connected to drone");
  }
}
 