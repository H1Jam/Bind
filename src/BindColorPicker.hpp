#ifndef __BINDCOLORPICKER_HPP
#define __BINDCOLORPICKER_HPP
#include "BindView.h"
#include "BindUtils.hpp"
class BindColorPicker : public BindView
{
private:
    uint8_t objID = BindIDs::colorPicker;
    uint16_t offset = 0;

public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t dimSize = 200;
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint16_t getBytes(uint8_t *out) override
    {
        offset = 0;
        copyAndOffset(out, &offset, &objID, sizeof(objID));
        copyAndOffset(out, &offset, &x, sizeof(x));
        copyAndOffset(out, &offset, &y, sizeof(y));
        copyAndOffset(out, &offset, &tag, sizeof(tag));
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
        copyAndOffset(out, &offset, &red, sizeof(red));
        copyAndOffset(out, &offset, &green, sizeof(green));
        copyAndOffset(out, &offset, &blue, sizeof(blue));
        return offset;
    }
};

#endif /* __BINDCOLORPICKER_HPP */
