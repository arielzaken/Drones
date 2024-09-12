#include "MSPSensor.h"

MSPResult *MSPSensor::read()
{
    MspAnswer mspAns = msp.sendMSPFromFC(sensorCode());
    if(mspAns.valid){
        MSPResult* result = getInstance();
        result->fill(mspAns.data, mspAns.dataLen);
        return result;
    }
    return nullptr;
}