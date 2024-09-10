#ifndef MSP_ANSWER_H
#define MSP_ANSWER_H

#define MSP_ANSWER_DATA_SIZE 128

typedef struct MspAnswer{
  uint8_t data[MSP_ANSWER_DATA_SIZE];
  uint8_t dataLen;
  uint8_t dataType;
  bool valid;
} MspAnswer;

#endif