#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "msp/Msp.h"
#include "ibus/ibus.h"
#include "mspDataFormat.h"

#define ARM_CHANNEL 4
#define ARM_VAL 1800
#define DISARM_VAL 1000
#define ARM_DEFULATE_VALUE 1000

#define ROLL_CHANNEL 0
#define ROLL_DEFAULT_VALUE 1500

#define PITCH_CHANNEL 1
#define PITCH_DEFAULT_VALUE 1500

#define YAW_CHANNEL 2
#define YAW_DEFAULT_VALUE 1500

#define THROTTLE_CHANNEL 3
#define THROTTLE_DEFAULT_VALUE 1000

#define AUX_DEFAULT_VALUE 1500

class Controller{
  ALTITUDE_DATA altData;
  ATTITUDE_DATA attData;
  COMP_GPS_DATA comData;
  RAW_GPS_DATA rawData;
  ANALOG_DATA analogData;

  bool armFlag = false;
public:
  void begin();
  void loop();

  void disconnect();
  void connect();

  // arm commands
  void arm();
  void disarm();
  bool isArmed() {return armFlag;};
  // setters for controller
  void setThrottle(uint16_t thr);
  void setRoll(uint16_t roll);
  void setPitch(uint16_t pit);
  void setYaw(uint16_t pit);
  void setAUX(uint8_t channel, uint16_t val);

  // getters for controller
  uint16_t getThrottle();
  uint16_t getRoll();
  uint16_t getPitch();
  uint16_t getYaw();
  uint16_t getAUX(uint8_t channel);

  // reset the controller to the default settings
  void resetThrottle();
  void resetRoll();
  void resetPitch();
  void resetYaw();
  void resetAUX(uint8_t channel);
  void resetChannels();

  // getters for the controller
  RAW_GPS_DATA getRawGPS(); // raw GPS data
  COMP_GPS_DATA getCompGPS(); // get the computed GPS data
  ATTITUDE_DATA getAttitude(); // get the attitude of the craft
  ALTITUDE_DATA getAltitude(); // get the altitude of the craft
  ANALOG_DATA getAnalog(); // get the analog values (only the battery volteg is worth it)
};


extern Controller controller;

#endif