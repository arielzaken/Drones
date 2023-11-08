#include <Arduino.h>
#include "Controller/Controller.h"



void setup() {
  Serial.begin(115200);
  controller.begin();
}

bool mspEnable = 0;
void loop() {
  if(Serial.available())
    switch((char)Serial.read()){
    case '0':
      controller.setThrottle(1000);
      Serial.println("sup");
      break;
    case '1':
      controller.setThrottle(1100);
      break;
    case '2':
      controller.setThrottle(1500);
      break;
    case 'a':
      controller.arm();
      break;
    case 'd':
      controller.disarm();
      break;
    }
  controller.loop();
}