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
}/**/

/*
#include "Controller/Controller.h"

void setup() {
  Serial.begin(115200);
  controller.begin();
}

bool mspEnable = 0;
//ALTITUDE_DATA altData;
void loop() {
  if(Serial.available()){
    switch((char)Serial.read()){
    case '0':
      controller.setThrottle(1000);
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
    case 'A':
      {
      ALTITUDE_DATA altData = controller.getAltitude();
      Serial.printf("alt: %d alt speed: %d\n",altData.EstAlt,altData.vario);
      break;
      }
    }  
  }
  controller.loop();
}/**/
/*
#include "Controller/ibus/ibus.h"
#include "Controller/msp/Msp.h"
#include "Controller/mspDataFormat.h"

ALTITUDE_DATA getAltitude(){
  ALTITUDE_DATA ans;
  MspAnswer mspAns;
  do{
    mspAns = msp.sendRequest(MSP_ALTITUDE);
  }while(!mspAns.valid);
  if(mspAns.valid){
    ans.EstAlt = mspAns.data[0] | mspAns.data[1] << 8 | mspAns.data[2] << 16 | mspAns.data[3] << 24 ;
    ans.vario = mspAns.data[4] | mspAns.data[5] << 8;
  }
  return ans;
}

void setup() {
  Serial.begin(115200);
  msp.begin(Serial2);

  ALTITUDE_DATA alt  = getAltitude();

  Serial.println(alt.EstAlt);
}

void loop() {
  
}
/**/
/*
#include "Operator/ProgramPlayer/ProgramPlayer.h"

ProgramPlayer PP;

void setup() {
  Serial.begin(115200);
  PP.reset();
}

void loop() {
  Serial.println(PP.getTime());
  delay(1000);
}/**/