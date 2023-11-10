#include <Arduino.h>
#include "Operator/Operator.h"
/*
void setup() {
  Serial.begin(115200);
  OP.begin();
}

bool mspEnable = 0;
ALTITUDE_DATA altData;
void loop() {
  if(Serial.available())
    switch((char)Serial.read()){
    case 't':
      OP.takeOff();
      break;
    }
  OP.loop();
}/**/


/*#include "Controller/Controller.h"

void setup() {
  Serial.begin(115200);
  controller.begin();
}

bool mspEnable = 0;
ALTITUDE_DATA altData;
void loop() {
  if(Serial.available())
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
    case 'A':
      altData = controller.getAltitude();
      Serial.printf("alt: %d alt speed: %d\n",altData.EstAlt,altData.vario);
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

/*#include "Controller/ibus/ibus.h"
#include "Controller/msp/Msp.h"

uint16_t val[14] = {
  1500,
  1500,
  1500,
  800,
  1000,
  1500
};

void setup() {
  Serial.begin(115200);
  msp.begin(Serial2);
  ibus.begin(Serial1, 4 , 2); //RX: GPIO4 TX: GPIO2
  ibus.enable();
}
MspAnswer ans;
void loop1() {
  Serial.println('e');
  ans = msp.sendRequest(MSP_ALTITUDE);
  if(ans.valid){
    int16_t accx = ans.data[0] | (ans.data[1] << 8);
    int16_t accy = ans.data[2] | (ans.data[3] << 8);
    int16_t accz = ans.data[4] | (ans.data[5] << 8);
  }
  delay(100);
}
bool mspEnable = 0;
void loop() {
  if(Serial.available()){
    switch((char)Serial.read()){
    case '0':
      val[3] = 1000;
      break;
    case '1':
      val[3] = 1100;
      break;
    case '2':
      val[3] = 1500;
      break;
    case 'a':
      val[4] = 1800;
      break;
    case 'd':
      val[4] = 1000;
      break;
    case 'M':
      mspEnable = !mspEnable;
      break;
    }
    ibus.setControlValuesList(val);
  }
  ibus.loop();
  if(mspEnable)
    loop1();
}*/
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