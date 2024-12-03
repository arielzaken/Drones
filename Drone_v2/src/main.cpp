#include "Arduino.h"
#include "mock/ControllerMock/ControllerMock.h"
#include "Protocol/Controllers/P3I/P3I.h"

float res;

ControllerMock cm;

P3I controller(1, 5);

void printTask(void* arg){
    Serial.printf("printTask created\n");
    for(;;){
        cm.print(Serial);
        Serial.println(cm.getVelocity()[Z]);
        Serial.println(res);
        delay(100);
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
    // res = controller.update(0, 750.0f);
    // Serial.println(res);

}

void loop() {
    res = controller.update(10, cm.getVelocity()[Z]);
    cm.setThrottle(1000 + res);
}
