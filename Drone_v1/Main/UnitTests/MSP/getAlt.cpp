#include <Arduino.h>
#include "Controller/msp/Msp.h"
#include "Controller/mspDataFormat.h"

ALTITUDE_DATA cal(){
  MspAnswer mspAns;
  do{
    mspAns = msp.sendMSPFromFC(MSP_ALTITUDE);
  }while(!mspAns.valid);
  ALTITUDE_DATA ans;
  if(mspAns.valid){
    ans.EstAlt = mspAns.data[0] | mspAns.data[1] << 8 | mspAns.data[2] << 16 | mspAns.data[3] << 24 ;
    ans.vario = mspAns.data[4] | mspAns.data[5] << 8;
  }
  return ans;
}

void setup() {
  Serial.begin(115200);
  msp.begin(Serial2);

  ALTITUDE_DATA alt  = cal();

  Serial.println(alt.EstAlt);
}

void loop() {
  
}