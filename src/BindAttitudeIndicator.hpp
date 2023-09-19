#ifndef __BINDATTITUDEINDICATOR_HPP
#define __BINDATTITUDEINDICATOR_HPP
#include "BindViewAutoTag.hpp"
#include "BindUtils.hpp"
class BindAttitudeIndicator : public BindViewAutoTag
{
private:
    uint8_t objID = BindIDs::attitudeIndicator;
    uint16_t offset = 0;

public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t dimSize = 200;
    float roll = 0.0f;
    float pitch = 0.0f;
    uint16_t getBytes(uint8_t *out) override
    {
        offset = 0;
        copyAndOffset(out, &offset, &objID, sizeof(objID));
        copyAndOffset(out, &offset, &x, sizeof(x));
        copyAndOffset(out, &offset, &y, sizeof(y));
        copyAndOffset(out, &offset, &tag, sizeof(tag));
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
        copyAndOffset(out, &offset, &roll, sizeof(roll));
        copyAndOffset(out, &offset, &pitch, sizeof(pitch));
        return offset;
    }
};

#endif /* __BINDATTITUDEINDICATOR_HPP */
