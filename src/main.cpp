#include <Arduino.h>
#include "Controller/Controller.h"

void setup() {
    Serial.begin(115200);
    controller.begin();
}

//ALTITUDE_DATA altData;
void loop() {
    if(Serial.available()){
        switch((char)Serial.read()){
        case '0':
            controller.setThrottle(1000);
            break;
        case '1':
            controller.setThrottle(1100);
            break;
        case '2':
            controller.setThrottle(1500);
            break;
        case 'a':
            controller.arm();
            break;
        case 'd':
            controller.disarm();
            break;
        case 'A':
        {
            ALTITUDE_DATA altData = controller.getAltitude();
            Serial.printf("alt: %d alt speed: %d\n",altData.EstAlt,altData.vario);
            break;
        }
        case 'c':
            if(controller.accCalibration())
                Serial.println("acc calibrationetad");
            break;
        }  
    }
    controller.loop();
}