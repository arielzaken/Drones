#include <Arduino.h>
#include "Operator/Operator.h"
//#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
	Serial.begin(115200);
	//SerialBT.begin("clone_drone_in_the_danger_zone");
	OP.begin(Serial);
}

void loop() {
	if(Serial.available())
		switch((char)Serial.read()){
		case 't':
			{
				Mission mission;
				mission.valid = true;
				mission.end_point = controller.getRawGPS();
				OP.setMission(mission);
			}
			break;
		case 'e':
			OP.emergencyLanding();
			break;
		case 'E':
			controller.disconnect();
			break;
		}
	OP.loop();
}