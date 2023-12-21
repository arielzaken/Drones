#include <Arduino.h>


// xbox controller interface
#include "Controller/Controller.h"
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
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
/**/
/*
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
}/**/



/*

#include "Operator/Operator.h"
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  SerialBT.begin("clone_drone_in_the_danger_zone");
  OP.begin();
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
    }
  OP.loop();
}/**/

/*
#include "Controller/Controller.h"

void setup() {
  Serial.begin(115200);
  controller.begin();
}

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
    case 'c':
      if(controller.accCalibration())
        Serial.println("acc calibrationetad");
      break;
    }  
  }
  controller.loop();
}/**/
/*
#include "Controller/ibus/ibus.h"
#include "Controller/msp/Msp.h"
#include "Controller/mspDataFormat.h"

void cal(){
  MspAnswer mspAns;
  do{
    mspAns = msp.sendMSPToFC(MSP_ACC_CALIBRATION);
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