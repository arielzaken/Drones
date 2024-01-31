#ifndef MISSION_h
#define MISSION_h
#include "Controller/Controller.h"

typedef struct Mission{
    bool valid;
    RAW_GPS_DATA end_point;
} Mission;

#endif