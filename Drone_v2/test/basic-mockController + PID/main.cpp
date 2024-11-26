#include "Arduino.h"
#include "DroneController/mock/ControllerMock.h"
#include "Protocol/PID/PID.h"
ControllerMock cm;
PID xPID(1, 0, 0, 200);
PID yPID(1, 0, 0, 200);
PID zPID(5, 1, 2, 250);
PID wPID(3, 0, 0, 200);

void printTask(void* arg){
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
        1024,
        NULL,
        1,
        NULL
    );
    // Serial.printf("printTask created\n");
    // delay(1000);
    // cm.setThrottle(1260);
    // Serial.printf("1260\n");
    // cm.setRoll(1510);
    delay(2000);
    // for (size_t i = 50; i >= -50; i--)
    // {
    //     cm.setThrottle(1250 + i);
    // }
    
}

int32_t out;
void loop() {
    // out = yPID.update(4000, cm.getPos().v.y);
    // cm.setRoll(1500 + out);
    // Serial.println(out);
    out = zPID.update(2000000, cm.getPos().v.z);
    cm.setThrottle(1250 + out);
    // Serial.println(out);
    delay(5);
}
