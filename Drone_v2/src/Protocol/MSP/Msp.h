/*
 * This file is part of the  distribution (https://github.com/wifi-drone-esp32 or http://wifi-drone-esp32.github.io).
 * Copyright (c) 2019 Michal Schwarz.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Ibus class is inspired by blogposts:
 *   https://basejunction.wordpress.com/2015/08/23/en-flysky-i6-14-channels-part1/
 *   http://blog.dsp.id.au/posts/2017/10/22/flysky-ibus-protocol/
 */

#ifndef Msp_h
#define Msp_h

#include "config.h"
#include "Arduino.h"
#include "MspAnswer.h"

enum state { START_STATE, SIZE_STATE, TYPE_STATE, DATA_STATE, CHECKSUM_STATE };

class Msp {
  public:
    static const unsigned long MSP_BAUD_RATE = 115200;

    void begin(HardwareSerial &serial);
    MspAnswer sendMSPFromFC(int req);
    MspAnswer sendMSPToFC(int req,uint8_t* data,int len);
  private:
    MspAnswer checkForAnswer();
    state stat;
    HardwareSerial *serial;
    static uint8_t request[5];
    uint8_t get_crc(uint8_t startCrc,uint8_t* data,int len);
};

extern Msp msp;

#endif


