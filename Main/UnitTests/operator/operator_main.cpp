#include <Arduino.h>
#include "Operator/Operator.h"

void setup() {
  Serial.begin(115200);
  OP.begin();
}

void loop() {
  if(Serial.available())
    switch((char)Serial.read()){
    case 't':
      OP.takeOff();
      break;
    case 'a':
      if(OP.arm())
        Serial.println("armed");
      break;
    case 'e':
      OP.emergencyLanding();
      break;
    }
  OP.loop();
}