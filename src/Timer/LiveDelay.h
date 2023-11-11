#ifndef LIVE_DELAY_H
#define LIVE_DELAY_H
#include "Arduino.h"

// this class is for doing delay without stopping the main loop
class LiveDelay{
    uint32_t delay;
    unsigned long last_time;
public:
    LiveDelay(): delay(0) {};
    LiveDelay(uint32_t delay): delay(delay) {};

    void setDelay(uint32_t d) {delay = d;};
    uint32_t getDelay() {return delay;};

    bool tryToActivate() {
        unsigned long now = millis();
        if(last_time <= now - (this->delay)){
            last_time = now;
            return true;
        }
        return false;
    }
};


#endif // LIVE_DELAY_H