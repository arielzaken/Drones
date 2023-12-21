#include <Arduino.h>


/*
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
}/**/
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

#include "algorithems/PID/PID_v1.h"
#define ERRORPASS 0.1

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,37,5,25,P_ON_E, DIRECT); //P_ON_M specifies that Proportional on Measurement be used
                                                            //P_ON_E (Proportional on Error) is the default behavior

void setup()
{
  Serial.begin(112500);
  //initialize the variables we're linked to
  Setpoint = 20;
  Input = 0;
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(1000,1500);

  srand((unsigned) time(NULL));
}

double kp = 37;
double ki = 5;
double kd = 25;

const int interval = 1000;

void loop()
{
  double v = 0;
  Input = 0;
  int hit = 0;
  for (size_t i = 0; i < interval; i++)
  {
    myPID.Compute();

    v += ((Output-1000)*0.04-10+(rand()%100-50)*0.05) * 0.01;
    Input += v * 0.01;
    Input += (rand()%101-50)*0.0024;
    //Serial.printf("Setpoint: % 7.3f Input: % 7.3f Output: % 7.3f\n", Setpoint, Input, Output);
    if(Input > Setpoint-ERRORPASS && Input < Setpoint+ERRORPASS)
      hit++;
    delay(10);
  }
  
  double cost = 1.0 - (static_cast<double>(hit) / interval); // Calculate the cost

  // Gradient descent update rule for each PID parameter
  double learningRate = 0.01; // Define the learning rate
  double deltaKp = learningRate * (2 * kp * cost); // Update delta for kp
  double deltaKi = learningRate * (2 * ki * cost); // Update delta for ki
  double deltaKd = learningRate * (2 * kd * cost); // Update delta for kd

  // Update PID parameters
  kp -= deltaKp;
  ki -= deltaKi;
  kd -= deltaKd;
  myPID.SetTunings(kp, ki, kd);
  Serial.printf("PID parameters kp: % 7.3f ki: % 7.3f kd: % 7.3f\n  hits: %d", kp, ki, kd, hit);
}