#include "Controller.h"

Controller controller;

void Controller::begin(){
  msp.begin(Serial2);
  ibus.begin(Serial1, 4, 2);
  resetChannels();
  delay(100);
  arm();
}

void Controller::loop(){
  ibus.loop();
}

void Controller::setAUX(uint8_t channel, uint16_t val){
  if(channel > 0 && channel < IBUS_CHANNELS_COUNT-3)
    ibus.setChannel(channel+3,val);
}

void Controller::resetThrottle(){
  setThrottle(THROTTLE_DEFAULT_VALUE);
}

void Controller::resetRoll(){
  setRoll(ROLL_DEFAULT_VALUE);
}

void Controller::resetPitch(){
  setPitch(PITCH_DEFAULT_VALUE);
}

void Controller::resetYaw(){
  setYaw(YAW_DEFAULT_VALUE);
}

void Controller::resetAUX(uint8_t channel){
  setAUX(channel, AUX_DEFAULT_VALUE);
}

void Controller::resetChannels(){
  resetThrottle();
  resetPitch();
  resetRoll();
  resetYaw();
  for(uint8_t i=1; i<IBUS_CHANNELS_COUNT-3; i++)
    resetAUX(i);
}

void Controller::arm(){
  //TODO: check if there isent somthing in the way.
  ibus.setChannel(ARM_CHANNEL, ARM_VAL);
}

void Controller::disarm(){
  ibus.setChannel(ARM_CHANNEL, DISARM_VAL);
}

void Controller::setRoll(uint16_t roll){
  ibus.setChannel(ROLL_CHANNEL, roll);
}

void Controller::setPitch(uint16_t pit){
  ibus.setChannel(PITCH_CHANNEL, pit);
}

void Controller::setYaw(uint16_t yaw){
  ibus.setChannel(YAW_CHANNEL, yaw);
}

void Controller::setThrottle(uint16_t tho){
  ibus.setChannel(THROTTLE_CHANNEL, tho);
}

ALTITUDE_DATA Controller::getAltitude(){
  ALTITUDE_DATA ans;
  MspAnswer mspAns = msp.sendRequest(MSP_ALTITUDE);
  if(mspAns.valid){
    ans.EstAlt = mspAns.data[0] | mspAns.data[1] << 8 | mspAns.data[2] << 16 | mspAns.data[3] << 24 ;
    ans.vario = mspAns.data[4] | mspAns.data[5] << 8;
  }
  return ans;
}







