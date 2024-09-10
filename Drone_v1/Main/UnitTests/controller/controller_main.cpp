#include <Arduino.h>
#include "Controller/Controller.h"
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("clone_drone_in_the_danger_zone");
  controller.begin();
  while(!SerialBT.connected()) delay(1);  
}

//ALTITUDE_DATA altData;
void loop() {
  if(SerialBT.available()){
    switch((char)SerialBT.read()){
    case 't':
    {
      String thString = SerialBT.readStringUntil('\n');
      int th = thString.toInt();
      controller.setThrottle(th);   
    }
      break;
    case 'a':
      controller.arm();
      break;
    case 'd':
      controller.disarm();
      break;
    case 'A':
      {
      ALTITUDE_DATA altData = controller.getAltitude();
      SerialBT.printf("alt: %d alt speed: %d\n",altData.EstAlt,altData.vario);
      break;
      }
    case 'c':
      if(controller.accCalibration())
        SerialBT.println("acc calibrationetad");
      break; 
    }  
  }
  if (!SerialBT.connected()) {
    controller.disconnect();
  }
  controller.loop();
}