#ifndef GPS_H
#define GPS_H
#include <stdint.h>
#include "config.h"


typedef struct GPS_pos{
    uint32_t GPS_cord_lat; // the latatude coordinet    1 / 10 000 000 deg
    uint32_t GPS_cord_lon; // the longatude coordinet   1 / 10 000 000 deg
    bool isEqual(const GPS_pos otherPoint){
        if(abs(acos(sin(this.GPS_cord_lat)*sin(otherPoint.GPS_cord_lat)+
        cos(this.GPS_cord_lat)*cos(otherPoint.GPS_cord_lat)*cos(otherPoint.GPS_cord_lon-this.GPS_cord_lat))*6371)/100000>=ERROR_RADIUS)
            return true;
        return false;    
    }
} GPS_pos;

#endif /* GPS_H */