#include "Controller.h"

Controller controller;

void Controller::begin(){
  msp.begin(Serial2);
  ibus.begin(Serial1, 4, 2);
  resetChannels();
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

ANALOG_DATA Controller::getAnalog()
{
  ANALOG_DATA ans;
  MspAnswer mspAns = msp.sendRequest(MSP_ALTITUDE);
  if(mspAns.valid){
    ans.vbat = mspAns.data[0];
    ans.intPowerMeterSum = mspAns.data[1] | mspAns.data[2] << 8;
    ans.rssi = mspAns.data[3] | mspAns.data[4] << 8;
    ans.amperage = mspAns.data[5] | mspAns.data[6] << 8;
  }
  return ans;
}


RAW_GPS_DATA Controller::getRawGPS()
{
  RAW_GPS_DATA ans;
  MspAnswer mspAns = msp.sendRequest(MSP_ALTITUDE);
  if(mspAns.valid){
    ans.GPS_FIX = mspAns.data[0];
    ans.GPS_numSat = mspAns.data[1];
    ans.GPS_cord_lat = mspAns.data[2] | mspAns.data[3] << 8 | mspAns.data[3] << 16 | mspAns.data[4] << 24;
    ans.GPS_cord_lon = mspAns.data[5] | mspAns.data[6] << 8 | mspAns.data[7] << 16 | mspAns.data[8] << 24;
    ans.GPS_altitude = mspAns.data[9] | mspAns.data[10] << 8;
    ans.GPS_speed = mspAns.data[11] | mspAns.data[12] << 8; 
    ans.GPS_ground_course = mspAns.data[13] | mspAns.data[14] << 8; 
  }
  return ans;
}

COMP_GPS_DATA Controller::getCompGPS()
{
  COMP_GPS_DATA ans;
  MspAnswer mspAns = msp.sendRequest(MSP_ALTITUDE);
  if(mspAns.valid){
    ans.GPS_distanceToHome = mspAns.data[0] | mspAns.data[1] << 8;
    ans.GPS_directionToHome = mspAns.data[2] | mspAns.data[3] << 8;
    ans.GPS_update = mspAns.data[4];
  }
  return ans;
}

ATTITUDE_DATA Controller::getAttitude()
{
  ATTITUDE_DATA ans;
  MspAnswer mspAns = msp.sendRequest(MSP_ALTITUDE);
  if(mspAns.valid){
    ans.angx = mspAns.data[0] | mspAns.data[1] << 8 ;
    ans.angy = mspAns.data[2] | mspAns.data[3] << 8 ;
    ans.heading = mspAns.data[4] | mspAns.data[5] << 8;
  }
  return ans;
}
