#ifndef __BINDHEADINGINDICATOR_HPP
#define __BINDHEADINGINDICATOR_HPP
#include "BindViewAutoTag.hpp"
#include "BindUtils.hpp"
class BindHeadingIndicator : public BindViewAutoTag
{
private:
    uint8_t objID = BindIDs::headingIndicator;
    uint16_t offset = 0;

public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t dimSize = 200;
    float heading = 0.0f;
    uint16_t getBytes(uint8_t *out) override
    {
        offset = 0;
        copyAndOffset(out, &offset, &objID, sizeof(objID));
        copyAndOffset(out, &offset, &x, sizeof(x));
        copyAndOffset(out, &offset, &y, sizeof(y));
        copyAndOffset(out, &offset, &tag, sizeof(tag));
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
        copyAndOffset(out, &offset, &heading, sizeof(heading));
        return offset;
    }
};

#endif /* __BINDHEADINGINDICATOR_HPP */
