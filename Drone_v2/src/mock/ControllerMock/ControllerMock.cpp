#include "ControllerMock.h"
#include <Arduino.h>


void ControllerMock::setThrottle(uint16_t _throttle)
{
    if(_throttle > 2000) 
        this->throttle = 2000;
    else if(_throttle < 1000)
        this->throttle = 1000;
    else
        this->throttle = _throttle;
}

void ControllerMock::setPitch(uint16_t _pitch)
{
    if(_pitch > 2000) 
        this->pitch = 2000;
    else if(_pitch < 1000)
        this->pitch = 1000;
    else
        this->pitch = _pitch;
}

void ControllerMock::setYaw(uint16_t _yaw)
{
    if(_yaw > 2000) 
        this->yaw = 2000;
    else if(_yaw < 1000)
        this->yaw = 1000;
    else
        this->yaw = _yaw;
}

void ControllerMock::setRoll(uint16_t _roll)
{
    if(_roll > 2000) 
        this->roll = 2000;
    else if(_roll < 1000)
        this->roll = 1000;
    else
        this->roll = _roll;
}

void ControllerMock::setAUX(uint16_t channle, uint16_t auxValue)
{
    Serial.printf("mock setAUX not implemented!!\n");
}

void ControllerMock::arm()
{
    Serial.printf("mock arm not implemented!!\n");
}

void ControllerMock::disarm()
{
    Serial.printf("mock disarm not implemented!!\n");
}

void ControllerMock::disable()
{
    if(this->taskHandle){
        vTaskDelete(this->taskHandle);
        this->taskHandle = nullptr;
        Serial.printf("mock controller deleted\n");
    }
}

void ControllerMock::enable()
{
    if(this->taskHandle == nullptr){
        xTaskCreate(
            mockControllerLoop,
            "mockControllerLoop",
            2048,
            this,
            1,
            &(this->taskHandle)
        );
        Serial.printf("mock controller created\n");
    }
}

void ControllerMock::print(Print &out)
{
    out.printf("(%5.2f, %5.2f, %5.2f, %5.2f) | t:%u y:%u r:%u p:%u\n"
            , pos[X], pos[Y], pos[Z], pos[W], throttle, yaw, roll, pitch);
    //out.printf(" | %d, %d, %d, %d\n", throttle, roll, yaw, pitch);
}

Pos ControllerMock::getPos()
{
    return pos;
}

Velocity ControllerMock::getVelocity()
{
    return vel;
}

//static portMUX_TYPE pMT;

void mockControllerLoop(void* arg){
    ControllerMock* This = (ControllerMock*)arg;
    uint64_t lastTime = millis();
    uint64_t firstTime;
    for(;;){
        //taskENTER_CRITICAL(&pMT);
        firstTime = millis();
        float diff = (float)(firstTime - lastTime) / 1000;

        Pos lastPos = This->pos;

        This->pos[X] += (float)(This->yaw - 1500) * diff;
        This->pos[Y] += (float)(This->yaw - 1500) * diff; 

        float tempz = This->pos[Z] + (float)(This->throttle - 1250) * diff; 
        This->pos[Z] = tempz > 0 ? tempz : 0; 

        This->pos[W] += (float)(This->pitch - 1500) * diff; 
        
        This->vel = (This->pos - lastPos) * (1/diff);

        lastTime = firstTime;
        //taskEXIT_CRITICAL(&pMT);
        delay(1);
    }
    vTaskDelete(nullptr);
}
