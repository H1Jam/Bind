#ifndef __BINDBUTTON_H
#define __BINDBUTTON_H
#include "BindView.h"
#include "BindUtils.hpp"
// TODO: Extract the class to a serprate .h and .c file! Now!
// TODO: Add the class summaries!
class BindButton : public BindView
{
private:
  uint8_t objID = BindIDs::button;
  uint16_t offset = 0;
  int strLength = 0;
  const char *str;

public:
  BindButton(const char *cstr)
  {
    setlabel(cstr);
  }
  BindButton()
  {
    setlabel("Button");
  }
  int16_t x;
  int16_t y;
  uint8_t cmdId = 0;
  int16_t fontSize;
  int32_t color;
  int32_t backColor;
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
    copyAndOffset(out, &offset, &fontSize, sizeof(fontSize));
    copyAndOffset(out, &offset, &color, sizeof(color));
    copyAndOffset(out, &offset, &backColor, sizeof(backColor));
    copyAndOffset(out, &offset, str, strLength);
    return offset;
  }
};
#endif /* __BINDBUTTON_H */