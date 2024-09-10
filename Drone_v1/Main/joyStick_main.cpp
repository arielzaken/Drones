#include <Arduino.h>
#include <BluetoothSerial.h>
#include "Controller/Controller.h"

BluetoothSerial SerialBT;

void setup() {
  //Serial.begin(9600);
  SerialBT.begin("clone_drone_in_the_danger_zone");
  controller.begin();
  while(!SerialBT.connected()) delay(1);  
}

byte buffer[10]; // Assuming each channel value is a 2-byte integer

//ALTITUDE_DATA altData;
void loop() {
  if (SerialBT.available()) {
    // Read the bytes into the buffer
    SerialBT.readBytes(buffer, 10);
    controller.setThrottle(buffer[0] | (buffer[1] << 8));
    controller.setRoll(buffer[2] | (buffer[3] << 8));
    controller.setPitch(buffer[4] | (buffer[5] << 8));
    controller.setYaw(buffer[6] | (buffer[7] << 8));
    controller.setAUX(1, buffer[8] | (buffer[9] << 8));
  }
  
  if (!SerialBT.connected()) {
    controller.disconnect();
  }

  controller.loop();
} 