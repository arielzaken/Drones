#pragma once

#include "Sensors/MSPSensor/MSPResult.h"
#include <string.h>

class MSPAltitudeResult : public MSPResult{
    int32_t EstAlt;  // the altitude of the drone         [cm]
    int16_t vario;   // the veriaion of the altitude      [cm/s]
public:
    /**
     * @overload MSPResult
     */
    virtual void fill(uint8_t* data, uint8_t size)  override{
        memcpy(data,&EstAlt, 4);
        memcpy(data+4,&vario, 2);
    }
};