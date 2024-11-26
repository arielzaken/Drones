#include "Arduino.h"
#include "DroneController/mock/ControllerMock.h"
#include "Protocol/PID/PID.h"
ControllerMock cm;

void printTask(void* arg){
    Serial.printf("printTask created\n");
    for(;;){
        cm.print(Serial);
        delay(30);
    }
}

void setup() {
	Serial.begin(115200);
    cm.enable();
    xTaskCreate(
        printTask,
        "printTask",
        2048,
        NULL,
        1,
        NULL
    );
    delay(1000);
    // cm.setThrottle(1260);
    // Serial.printf("1260\n");
    // cm.setRoll(1510);
    // delay(2000);
    for (int i = 50; i >= -50; i--)
    {
        Serial.printf("%d\n", i);
        cm.setThrottle(1250 + i);
        delay(100);
    }
    
}

// int32_t out;
void loop() {
    // out = yPID.update(4000, cm.getPos().v.y);
    // cm.setRoll(1500 + out);
    // Serial.println(out);
    // out = zPID.update(2000000, cm.getPos().v.z);
    // cm.setThrottle(1250 + out);
    // // Serial.println(out);
    // delay(5);
}
