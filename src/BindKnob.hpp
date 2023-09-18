#ifndef __BINDKNOB_H
#define __BINDKNOB_H
#include "BindView.h"
#include "BindUtils.hpp"
// TODO: Extract the class to a serprate .h and .c file! Now!
// TODO: Add the class summaries!
class BindKnob : public BindView
{
private:
  uint8_t objID = BindIDs::knob;
  uint16_t offset = 0;
  int strLength = 0;
  const char *str;

public:
  BindKnob(const char *cstr)
  {
    setlabel(cstr);
  }
  BindKnob()
  {
    setlabel("Knob");
  }
  int16_t x;
  int16_t y;
  uint8_t cmdId = 0;
  int16_t dimSize;
  int16_t minValue;
  int16_t maxValue;
  int16_t value;
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
    copyAndOffset(out, &offset, str, strLength);
    return offset;
  }
};
#endif /* __BINDKNOB_H */