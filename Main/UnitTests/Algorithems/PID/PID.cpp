#include <Arduino.h>
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