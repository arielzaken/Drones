#include "IbusDroneController.h"

void IbusDroneController::setThrottle(uint16_t throttle)
{
    ibus.setChannel(THROTTLE_CHANNEL, throttle);
}

void  IbusDroneController::arm()
{
	ibus.setChannel(ARM_CHANNEL, ARM_VAL);
}

void  IbusDroneController::disarm(){
	ibus.setChannel(ARM_CHANNEL, DISARM_VAL);
}

void IbusDroneController::disable()
{
    ibus.disable();
}

void IbusDroneController::enable()
{
    ibus.enable();
}

void  IbusDroneController::setRoll(uint16_t roll){
  	ibus.setChannel(ROLL_CHANNEL, roll);
}

void  IbusDroneController::setPitch(uint16_t pit){
 	ibus.setChannel(PITCH_CHANNEL, pit);
}

void  IbusDroneController::setYaw(uint16_t yaw){
  	ibus.setChannel(YAW_CHANNEL, yaw);
}

void IbusDroneController::setAUX(uint16_t channel, uint16_t val){
  	if(channel > 0 && channel < IBUS_CHANNELS_COUNT-3)
    	ibus.setChannel(channel+3,val);
}