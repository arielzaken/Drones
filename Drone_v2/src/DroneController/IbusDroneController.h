#include "DroneController/DroneControllerInterface.h"
#include "Protocol/ibus/ibus.h"
class IbusDroneController : public DroneControllerInterface{
    virtual void setThrottle(uint16_t throttle);
    virtual void setPitch(uint16_t pitch);
    virtual void setYaw(uint16_t yaw);
    virtual void setRoll(uint16_t roll);
    virtual void setAUX( uint16_t channle ,uint16_t auxValue);

    virtual void arm();
    virtual void disarm();
    virtual void disable();
    virtual void enable();
};