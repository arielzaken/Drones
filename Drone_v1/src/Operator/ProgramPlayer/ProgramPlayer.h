#ifndef PROGRAM_PLAYER_H
#define PROGRAM_PLAYER_H
#include "Arduino.h"


/// @brief a calss to give functions "time" dimention in the local loop 
class ProgramPlayer{
    /// @brief the current cycle
    volatile uint64_t time = 0; 
    unsigned long last_time;
public:
    void reset() { 
        time = 0; 
        last_time = millis();
    };
    unsigned long getTime() {
        unsigned long current = millis();
        time += current - last_time;
        last_time = current;
        return time; 
    };

};



#endif // PROGRAM_PLAYER_H