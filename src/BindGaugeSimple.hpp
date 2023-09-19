#ifndef __BINDGAUGESIMPLE_HPP
#define __BINDGAUGESIMPLE_HPP
#include "BindViewAutoTag.hpp"
#include "BindUtils.hpp"

class BindGaugeSimple : public BindViewAutoTag
{
private:
    uint8_t objID = BindIDs::gaugeSimple;
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;

public:
    BindGaugeSimple(const char *cstr)
    {
        setlabel(cstr);
    }
    BindGaugeSimple()
    {
        setlabel("Gauge");
    }
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t dimSize = 200;
    int16_t minValue = 0;
    int16_t maxValue = 100;
    int16_t value = 0;
    uint8_t style = 0;
    bool isSymmetrical = false;
    int32_t color;
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
        copyAndOffset(out, &offset, &x, sizeof(x));
        copyAndOffset(out, &offset, &y, sizeof(y));
        copyAndOffset(out, &offset, &tag, sizeof(tag));
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
        copyAndOffset(out, &offset, &minValue, sizeof(minValue));
        copyAndOffset(out, &offset, &maxValue, sizeof(maxValue));
        copyAndOffset(out, &offset, &value, sizeof(value));
        copyAndOffset(out, &offset, &style, sizeof(style));
        copyAndOffset(out, &offset, &isSymmetrical, sizeof(isSymmetrical));
        copyAndOffset(out, &offset, &color, sizeof(color));
        copyAndOffset(out, &offset, str, strLength);
        return offset;
    }
};

#endif /* __BINDGAUGESIMPLE_HPP */
