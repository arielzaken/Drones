#include "Arduino.h"
#include "mock/ControllerMock/ControllerMock.h"
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
    // Serial.printf("1260\n");
    // cm.setRoll(1510);
    // delay(2000);
}

float acc = 0;
void loop() {
    float error = 5000-cm.getPos()[Z];
    cm.setThrottle(1000 + error * error * error + acc * 5);
    acc = (acc + error > 100 || acc + error < -100) ? 0 : acc + error;
}
