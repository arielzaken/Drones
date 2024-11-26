#include "controllerMock.h"
#include <Arduino.h>

void controllerMock::setThrottle(uint16_t throttle)
{
    this->throttle = throttle;
}

void controllerMock::setPitch(uint16_t pitch)
{
    this->pitch = pitch;
}

void controllerMock::setYaw(uint16_t yaw)
{
    this->yaw = yaw;
}

void controllerMock::setRoll(uint16_t roll)
{
    this->roll = roll;
}

void controllerMock::setAUX(uint16_t channle, uint16_t auxValue)
{
    Serial.printf("mock setAUX not implemented!!\n");
}

void controllerMock::arm()
{
    Serial.printf("mock arm not implemented!!\n");
}

void controllerMock::disarm()
{
    Serial.printf("mock disarm not implemented!!\n");
}

void controllerMock::disable()
{
    if(this->taskHandle){
        vTaskDelete(this->taskHandle);
        this->taskHandle = nullptr;
        Serial.printf("mock controller deleted\n");
    }
}

void controllerMock::enable()
{
    xTaskCreate(
        mockControllerLoop,
        "mockControllerLoop",
        1024,
        this,
        1,
        &(this->taskHandle)
    );
    Serial.printf("mock controller created\n");
}

void mockControllerLoop(void* arg){
    controllerMock* This = (controllerMock*)arg;
    uint64_t lastTime = millis();
    for(;;){
        This->pos.x
        
    }

    vTaskDelete(nullptr);
}
