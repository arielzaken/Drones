#ifndef GPS_H
#define GPS_H
#include <stdint.h>

typedef struct GPS_pos{
    uint32_t GPS_cord_lat; // the latatude coordinet    1 / 10 000 000 deg
    uint32_t GPS_cord_lon; // the longatude coordinet   1 / 10 000 000 deg
    bool isEqual(const GPS_pos &GPS_cord_lat){
        
    }
};

#endif /* GPS_H */