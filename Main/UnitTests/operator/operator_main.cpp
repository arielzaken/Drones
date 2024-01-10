#include <Arduino.h>
#include "Operator/Operator.h"
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("clone_drone_in_the_danger_zone");
  OP.begin(Serial, SerialBT);
}

void loop() {
  if(SerialBT.available())
    switch((char)SerialBT.read()){
    case 't':
      OP.takeOff();
      break;
    case 'a':
      if(OP.arm())
        SerialBT.println("armed");
      break;
    case 'e':
      OP.emergencyLanding();
      break;
    case 'E':
      controller.disconnect();
      break;
    }
  OP.loop();
}