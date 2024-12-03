#include "Arduino.h"
#include "Operator/Stabilizer.h"
#include "Operator/Behaviors.h"
#include "Sensors/DistanceSensor/mock/disMock.h"
Stabilizer stab;
LandBehavior lb;
TransitBehavior tb;
disMock dm;
TakeoffBehavior tab(dm);


void setup() {
	Serial.begin(115200);
    stab.addBehavior(lb);
    stab.addBehavior(tb);
    stab.addBehavior(tab);
}

void loop() {
    Twist res = stab.calcTwist();
    res.print();
    Serial.println();
    delay(300);
}
