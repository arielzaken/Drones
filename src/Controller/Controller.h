#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "msp/Msp.h"
#include "ibus/ibus.h"
#include "mspDataFormat.h"

#define ARM_CHANNEL 4
#define ARM_VAL 1800
#define DISARM_VAL 1000
#define ROLL_CHANNEL 0
#define PITCH_CHANNEL 1
#define YAW_CHANNEL 2
#define THROTTLE_CHANNEL 3

class Controller{
public:
  void begin();
  void loop();

  RAW_GPS_DATA getRawGPS();
  COMP_GPS_DATA getCompGPS();
  ATTITUDE_DATA getAttitude();
  ALTITUDE_DATA getAltitude();
  ANALOG_DATA getAnalog();

  void arm();
  void disarm();
  void setThrottle(uint16_t thr);
  void setRoll(uint16_t roll);
  void setPitch(uint16_t pit);
  void setYaw(uint16_t pit);
  void setAUX(uint8_t channel, uint16_t val);
};


extern Controller controller;

#endif