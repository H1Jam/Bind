#ifndef __BINDJOYSTICK_HPP
#define __BINDJOYSTICK_HPP
#include "BindView.h"
#include "BindUtils.hpp"
class BindJoystick : public BindView
{
private:
    uint8_t objID = BindIDs::joystick;
    uint16_t offset = 0;

public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t dimSize = 200;
    int16_t sX = 0;
    int16_t sY = 0;
    bool springed = true;
    uint16_t getBytes(uint8_t *out) override
    {
        offset = 0;
        copyAndOffset(out, &offset, &objID, sizeof(objID));
        copyAndOffset(out, &offset, &x, sizeof(x));
        copyAndOffset(out, &offset, &y, sizeof(y));
        copyAndOffset(out, &offset, &tag, sizeof(tag));
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
        copyAndOffset(out, &offset, &springed, sizeof(springed));
        return offset;
    }
};

#endif /* __BINDJOYSTICK_HPP */
