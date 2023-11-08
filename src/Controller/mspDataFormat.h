#ifndef MSP_DATA_FORMATS_H
#define MSP_DATA_FORMATS_H

typedef struct RAW_GPS_DATA{
  uint8_t GPS_FIX;  // 0 or 1
  uint8_t GPS_numSat;  // the number of satelaits
  uint32_t GPS_cord_lat; // the latatude coordinet    1 / 10 000 000 deg
  uint32_t GPS_cord_lon; // the longatude coordinet   1 / 10 000 000 deg
  uint16_t GPS_altitude; // the aprocsemated altetude [m]
  uint16_t GPS_speed; // the speed of the craft       [cm/s]
  uint16_t GPS_ground_course; // i really dont know.. unit: degree*10
} RAW_GPS_DATA;

typedef struct COMP_GPS_DATA{
  uint16_t GPS_distanceToHome;  // [m]
  uint16_t GPS_directionToHome; // deg [-180,180]
  uint8_t GPS_update;           // a flag to indicate when a new GPS frame is received (the GPS fix is not dependent of this)
} COMP_GPS_DATA;

typedef struct ATTITUDE_DATA{
  int16_t angx;    // Range [-1800;1800] (unit: 1/10 degree)
  int16_t angy;    // Range [-900;900] (unit: 1/10 degree)
  int16_t heading; // Range [-180;180]
} ATTITUDE_DATA;

typedef struct ALTITUDE_DATA{
  int32_t EstAlt;  // the highte of this shit [cm]
  int16_t vario;   // the veriaion            [cm/s]
} ALTITUDE_DATA;

typedef struct ANALOG_DATA{
  uint8_t vbat;              // the volteg of the battery unit: 1/10 volt
  uint16_t intPowerMeterSum; // bru
  uint16_t rssi;             // not relevent...
  uint16_t amperage;          // just why.. 
} ANALOG_DATA;


#endif