#ifndef __BINDCOLORPICKERHANDLER_H
#define __BINDCOLORPICKERHANDLER_H
#include "Stream.h"
#include "BindColorPicker.hpp"
// TODO: Extract the class to a serprate .h and .c file! Now!
// TODO: Add the class summaries!
class ColorPickerHandler
{
private:
  void (*clickCallback)(uint8_t, uint8_t, uint8_t) = NULL;
  BindColorPicker *screenColorPicker = NULL;

public:
  
  ColorPickerHandler(BindColorPicker *screenColorPicker = NULL, void (*_clickCallback)(uint8_t, uint8_t, uint8_t) = NULL)
  {
    this->screenColorPicker = screenColorPicker;
    this->clickCallback = _clickCallback;
  }

  void update(uint8_t r, uint8_t g, uint8_t b)
  {
    if (this->screenColorPicker != NULL)
    {
      this->screenColorPicker->red = r;
      this->screenColorPicker->green  = g;
      this->screenColorPicker->blue = b;
    }
    if (this->clickCallback != NULL)
    {
      this->clickCallback(r, g, b);
    }
  }
};
#endif /* __BINDCOLORPICKERHANDLER_H */