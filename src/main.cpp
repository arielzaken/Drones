#include <Arduino.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X sensor;


// Uncomment this line to use long range mode. This
// increases the sensitivity of the sensor and extends its
// potential range, but increases the likelihood of getting
// an inaccurate reading because of reflections from objects
// other than the intended target. It works best in dark
// conditions.

//#define LONG_RANGE


// Uncomment ONE of these two lines to get
// - higher speed at the cost of lower accuracy OR
// - higher accuracy at the cost of lower speed

//#define HIGH_SPEED
//#define HIGH_ACCURACY


void setup()
{
	Serial.begin(9600);
	sensor.setDeviceMode(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
	if (!sensor.begin())
	{
		Serial.println("Failed to detect and initialize sensor!");
		while (1) {}
	}

	// Start continuous back-to-back mode (take readings as
	// fast as possible).  To use continuous timed mode
	// instead, provide a desired inter-measurement period in
	// ms (e.g. sensor.startContinuous(100)).
	sensor.startRangeContinuous();
}

void loop()
{
	//sensor.startMeasurement();
	if(sensor.isRangeComplete()){
		Serial.print(sensor.readRangeResult());
		if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
		//sensor.stopRangeContinuous();
		Serial.println();
	}
}