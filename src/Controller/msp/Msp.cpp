#include <stdint.h>
#include "HardwareSerial.h"
#include "Arduino.h"
#include "Msp.h"

Msp msp;
uint8_t Msp::request[5] = {'$', 'M', '<', 0, 0}; // the msp request structure: "$M<" <data size> <data type>

void Msp::begin(HardwareSerial& serial) { // begin the serial object
  this->serial = &serial;
  this->serial->begin(MSP_BAUD_RATE);
}
/*
send a requast for data
*/
MspAnswer Msp::sendRequest(int req) {
  request[4] = req;
  this->serial->write(request, sizeof(request));
  this->serial->write(get_crc(request+3, sizeof(request+3)));
  return checkForAnswer();
}

uint8_t Msp::get_crc(uint8_t* data, int len) {
  uint8_t crc = 0;
  for (int i = 0; i < len; i++)
    crc ^= data[i];
  return crc;
}

MspAnswer Msp::checkForAnswer() {
  MspAnswer ans;
  stat = START_STATE;
  uint8_t crc = 0;
  // Read and parse attitude data
  while (this->serial->available()) {
    switch(stat){
    case START_STATE:
      this->serial->readBytes(ans.data,3);
      stat = SIZE_STATE;
      break;
    case SIZE_STATE:
      ans.dataLen = this->serial->read();
      crc ^= ans.dataLen;
      stat = TYPE_STATE;
      break;
    case TYPE_STATE:
      ans.dataType = this->serial->read();
      crc ^= ans.dataType;
      stat = DATA_STATE;
      break;
    case DATA_STATE:
      for (uint8_t i = 0; i < ans.dataLen; i++) {
        ans.data[i] = this->serial->read();
        crc ^= ans.data[i];
      }
      stat = CHECKSUM_STATE;
      break;
    case CHECKSUM_STATE:
      ans.valid = (this->serial->read() == crc);
      break;
    }
  }
  return ans;
}
