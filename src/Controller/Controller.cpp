#include "Controller.h"

Controller controller;

void Controller::begin(){
  msp.begin(Serial2);
  ibus.begin(Serial1, 4, 2);
  resetChannels();
  altData.lDelay.setDelay(50);
  attData.lDelay.setDelay(20);
  comData.lDelay.setDelay(20);
  rawData.lDelay.setDelay(20);
  analogData.lDelay.setDelay(20);
}

void Controller::loop(){
  ibus.loop();
}

void Controller::disconnect()
{
  ibus.disable();
}

void Controller::connect()
{
  ibus.enable();
}

void Controller::setAUX(uint8_t channel, uint16_t val){
  if(channel > 0 && channel < IBUS_CHANNELS_COUNT-3)
    ibus.setChannel(channel+3,val);
}

uint16_t Controller::getThrottle()
{
  return ibus.getChannel(THROTTLE_CHANNEL);
}

uint16_t Controller::getRoll()
{
  return ibus.getChannel(ROLL_CHANNEL);
}

uint16_t Controller::getPitch()
{
  return ibus.getChannel(PITCH_CHANNEL);
}

uint16_t Controller::getYaw()
{
  return ibus.getChannel(YAW_CHANNEL);
}

uint16_t Controller::getAUX(uint8_t channel)
{
  return ibus.getChannel(channel+3);
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
  disarm();
  for(uint8_t i=2; i<IBUS_CHANNELS_COUNT-3; i++)
    resetAUX(i);
}


void Controller::arm(){
  //TODO: check if there isent somthing in the way.
  armFlag = true; 
  ibus.setChannel(ARM_CHANNEL, ARM_VAL);
}

void Controller::disarm(){
  armFlag = false; 
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
  if(altData.lDelay.tryToActivate()){
    MspAnswer mspAns = msp.sendMSPFromFC(MSP_ALTITUDE);
    if(mspAns.valid){
      altData.EstAlt = mspAns.data[0] | mspAns.data[1] << 8 | mspAns.data[2] << 16 | mspAns.data[3] << 24 ;
      altData.vario = mspAns.data[4] | mspAns.data[5] << 8;
    }
  }
  return altData;
}

ANALOG_DATA Controller::getAnalog()
{
  if(analogData.lDelay.tryToActivate()){
    MspAnswer mspAns = msp.sendMSPFromFC(MSP_ANALOG);
    if(mspAns.valid){
      analogData.vbat = mspAns.data[0];
      analogData.intPowerMeterSum = mspAns.data[1] | mspAns.data[2] << 8;
      analogData.rssi = mspAns.data[3] | mspAns.data[4] << 8;
      analogData.amperage = mspAns.data[5] | mspAns.data[6] << 8;
    }
  }
  return analogData;
}

bool Controller::accCalibration()
{
  MspAnswer mspAns = msp.sendMSPToFC(MSP_ACC_CALIBRATION,NULL,0);
  return mspAns.valid;
}

RAW_GPS_DATA Controller::getRawGPS()
{
  if(rawData.lDelay.tryToActivate()){
    MspAnswer mspAns = msp.sendMSPFromFC(MSP_RAW_GPS);
    if(mspAns.valid){
      rawData.GPS_FIX = mspAns.data[0];
      rawData.GPS_numSat = mspAns.data[1];
      rawData.GPS_cord_lat = mspAns.data[2] | mspAns.data[3] << 8 | mspAns.data[3] << 16 | mspAns.data[4] << 24;
      rawData.GPS_cord_lon = mspAns.data[5] | mspAns.data[6] << 8 | mspAns.data[7] << 16 | mspAns.data[8] << 24;
      rawData.GPS_altitude = mspAns.data[9] | mspAns.data[10] << 8;
      rawData.GPS_speed = mspAns.data[11] | mspAns.data[12] << 8; 
      rawData.GPS_ground_course = mspAns.data[13] | mspAns.data[14] << 8; 
    }
  }
  return rawData;
}

COMP_GPS_DATA Controller::getCompGPS()
{
  if(comData.lDelay.tryToActivate()){
    MspAnswer mspAns = msp.sendMSPFromFC(MSP_COMP_GPS);
    if(mspAns.valid){
      comData.GPS_distanceToHome = mspAns.data[0] | mspAns.data[1] << 8;
      comData.GPS_directionToHome = mspAns.data[2] | mspAns.data[3] << 8;
      comData.GPS_update = mspAns.data[4];
    }
  }
  return comData;
}

ATTITUDE_DATA Controller::getAttitude()
{
  if(attData.lDelay.tryToActivate()){
    MspAnswer mspAns = msp.sendMSPFromFC(MSP_ATTITUDE);
    if(mspAns.valid){
      attData.angx = mspAns.data[0] | mspAns.data[1] << 8 ;
      attData.angy = mspAns.data[2] | mspAns.data[3] << 8 ;
      attData.heading = mspAns.data[4] | mspAns.data[5] << 8;
    }
  }
  return attData;
}
