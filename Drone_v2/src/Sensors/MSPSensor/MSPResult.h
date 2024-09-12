#pragma once
#include <cstdint>

class MSPResult
{
public:
    virtual void fill(uint8_t* data, uint8_t size) = 0;
};