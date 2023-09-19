#ifndef __BINDSWITCH_HPP
#define __BINDSWITCH_HPP
#include "BindView.h"
#include "BindUtils.hpp"

class BindSwitch : public BindView
{
private:
    uint8_t objID = BindIDs::toggleSwitch;
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;

public:
    BindSwitch(const char *cstr)
    {
        setlabel(cstr);
    }
    BindSwitch()
    {
        setlabel("Switch");
    }
    int16_t x;
    int16_t y;
    uint8_t cmdId = 0;
    bool switchValue;
    int16_t fontSize;
    int32_t textColor;
    void setlabel(const char *cstr)
    {
        str = cstr;
    }
    uint16_t getBytes(uint8_t *out) override
    {
        offset = 0;
        strLength = strlen(str);
        if (strLength > MAX_STRING_LENGTH_TERMINAL)
        {
            strLength = MAX_STRING_LENGTH_TERMINAL;
        }
        copyAndOffset(out, &offset, &objID, sizeof(objID));
        copyAndOffset(out, &offset, &x, 2);
        copyAndOffset(out, &offset, &y, 2);
        copyAndOffset(out, &offset, &tag, 2);
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        copyAndOffset(out, &offset, &switchValue, sizeof(switchValue));
        copyAndOffset(out, &offset, &fontSize, sizeof(fontSize));
        copyAndOffset(out, &offset, &textColor, sizeof(textColor));
        copyAndOffset(out, &offset, str, strLength);
        return offset;
    }
};

#endif /* __BINDSWITCH_HPP */
