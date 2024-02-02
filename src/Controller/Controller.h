#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "msp/Msp.h"
#include "ibus/ibus.h"
#include "mspDataFormat.h"
#include "algorithems/PID/PID_v1.h"
#include "config.h"

class Controller{
	ALTITUDE_DATA altData;
	ATTITUDE_DATA attData;
	COMP_GPS_DATA comData;
	RAW_GPS_DATA rawData;
	ANALOG_DATA analogData;

	bool armFlag = false;
	double requiredAlt; // [m] the required altitude of the drone
	double currentAlt; // [m] the curent altitude of the drone
	double hoverThrottle; // [m] throttle

	bool altPIDEnabled = false;
	PID altPID = PID(
		&currentAlt, 
		&hoverThrottle, 
		&requiredAlt, 
		(double)ALT_PID_P, 
		(double)ALT_PID_I, 
		(double)ALT_PID_D, 
		P_ON_E, DIRECT);

public:
	void begin();
	void loop();

	void disconnect();
	void connect();

	void enableHover(){altPIDEnabled = true;}
	void disableHover(){altPIDEnabled = false;}

	// arm commands
	void arm();
	void disarm();
	bool isArmed() {return armFlag;};
	// setters for controller
	void setThrottle(uint16_t thr);
	void setRoll(uint16_t roll);
	void setPitch(uint16_t pit);
	void setYaw(uint16_t pit);
	void setAUX(uint8_t channel, uint16_t val);
	void setReqAlt(double reqAlt){requiredAlt = reqAlt;}

	// getters for controller
	uint16_t getThrottle();
	uint16_t getRoll();
	uint16_t getPitch();
	uint16_t getYaw();
	uint16_t getAUX(uint8_t channel);

	// reset the controller to the default settings
	void resetThrottle();
	void resetRoll();
	void resetPitch();
	void resetYaw();
	void resetAUX(uint8_t channel);
	void resetChannels();

	// getters for the controller
	RAW_GPS_DATA getRawGPS(); // raw GPS data
	COMP_GPS_DATA getCompGPS(); // get the computed GPS data
	ATTITUDE_DATA getAttitude(); // get the attitude of the craft
	ALTITUDE_DATA getAltitude(); // get the altitude of the craft
	ANALOG_DATA getAnalog(); // get the analog values (only the battery volteg is worth it)

	// setters for the controller
	bool accCalibration();
};


extern Controller controller;

#endif