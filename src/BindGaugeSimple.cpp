#include "BindGaugeSimple.hpp"

int16_t BindGaugeSimple::tagIndex = 1;

BindGaugeSimple::BindGaugeSimple(const char *cstr)
{
    this->tag = tagIndex++;
    setlabel(cstr);
}

uint16_t BindGaugeSimple::getBytes(uint8_t *out) 
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